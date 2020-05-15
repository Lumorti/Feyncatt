#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SD.h>
#include <avr/pgmspace.h>

// Address of the gyro
#define MPU_ADDR 0x68

// Servo properties
#define SERVO_FREQ 50
#define NUM_SERVOS 16
#define QUEUE_SIZE 5
#define NUM_POSITIONS 11
#define AVG_SPEED 100
#define SAVE_POWER false

// Servo pin numbers
#define FRONT_LEFT_HIP      0
#define FRONT_LEFT_KNEE     1
#define FRONT_LEFT_ANKLE    2
#define BACK_LEFT_HIP       4
#define BACK_LEFT_KNEE      5
#define BACK_LEFT_ANKLE     6
#define BACK_RIGHT_HIP      8
#define BACK_RIGHT_KNEE     9
#define BACK_RIGHT_ANKLE    10
#define FRONT_RIGHT_HIP     12
#define FRONT_RIGHT_KNEE    13
#define FRONT_RIGHT_ANKLE   14
#define NECK_VERT           3
#define NECK_HORIZ          15

// Position numbers
#define STOOD_STRAIGHT          0
#define FRONT_LEFT_LEG_UP       1
#define FRONT_RIGHT_LEG_UP      2

// Min and max values for each servo, tweak as necessary
const short minPWM[NUM_SERVOS]   PROGMEM = {110, 120, 120, 0, 130, 150, 110, 0, 105, 120, 120, 0, 120, 120, 110, 0};
const short midPWM[NUM_SERVOS]   PROGMEM = {290, 310, 315, 0, 325, 345, 305, 0, 310, 315, 325, 0, 325, 320, 310, 0};
const short maxPWM[NUM_SERVOS]   PROGMEM = {530, 520, 520, 0, 500, 545, 555, 0, 510, 520, 560, 0, 540, 520, 555, 0};
const short minAngle[NUM_SERVOS] PROGMEM = {-30, -90, -90, 0, -30, -90, -90, 0, -30, -90, -90, 0, -30, -90, -90, 0};
const short maxAngle[NUM_SERVOS] PROGMEM = { 30,  90,  90, 0,  30,  90,  90, 0,  30,  90,  90, 0,  30,  90,  90, 0};

const short positions[NUM_POSITIONS][NUM_SERVOS] PROGMEM = {

  // STOOD_STRAIGHT
  {0,   0,   0, 0, 0,   0,   0, 0, 0,   0,   0,  0, 0,   0,   0, 0},

  // FRONT_LEFT_UP
  {0,  45, -45, 0, 0,   0,   0, 0, 0,   0,   0,  0, 0,   0,   0, 0},
  // FRONT_RIGHT_UP
  {0,   0,   0, 0, 0,   0,   0, 0, 0,   0,   0,  0, 0, -45,  45, 0},
  // BACK_LEFT_UP
  {0,   0,   0, 0, 0,  45, -45, 0, 0,   0,   0,  0, 0,   0,   0, 0},
  // BACK_RIGHT_UP
  {0,   0,   0, 0, 0,   0,   0, 0, 0, -45,  45,  0, 0,   0,   0, 0},

  // WALK1 = FRONT_RIGHT_UP + BACK_LEFT_UP
  {0,   0,   0, 0, 0,  45, -45, 0, 0,   0,   0,  0, 0, -45,  45, 0},

  // WALK2 = FRONT_RIGHT_UP + BACK_LEFT_UP - FRONT_LEFT_UP - BACK_RIGHT_UP
  {0, -45,  45, 0, 0,  45, -45, 0, 0,  45, -45,  0, 0, -45,  45, 0},

  // WALK3 = - FRONT_LEFT_UP - BACK_RIGHT_UP
  {0, -45,  45, 0, 0,   0,   0, 0, 0,  45, -45,  0, 0,   0,   0, 0},

  // WALK1_ALT = FRONT_LEFT_UP + BACK_RIGHT_UP
  {0,  45, -45, 0, 0,   0,   0, 0, 0, -45,  45,  0, 0,   0,   0, 0},

  // WALK2_ALT = FRONT_LEFT_UP + BACK_RIGHT_UP - FRONT_RIGHT_UP - BACK_LEFT_UP
  {0,  45, -45, 0, 0, -45,  45, 0, 0, -45,  45,  0, 0,  45, -45, 0},

  // WALK3_ALT =  - FRONT_RIGHT_UP - BACK_LEFT_UP
  {0,   0,   0, 0, 0, -45,  45, 0, 0,   0,   0,  0, 0,  45, -45, 0},


};

// Main servo controller
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// For I/O
String soFar;
int newValue;
int motorNum;
char incomingByte;

// For accelerometer data
float accelData[3];

// For storing the current angle and the queue of positions
float currentAngles[NUM_SERVOS];
float deltas[NUM_SERVOS];
int stepsLeft = 0;
int numInQueue = 0;
int queue[QUEUE_SIZE * 2];

// Change a servo to an angle
void setServoAngle(uint8_t servoNum, double angle) {

  int actualAngle = min(max(angle, pgm_read_word_near(minAngle + servoNum)), pgm_read_word_near(maxAngle + servoNum));

  if (actualAngle < 0) {
    pwm.setPWM(servoNum, 0, map(actualAngle, -90, 0, pgm_read_word_near(minPWM + servoNum), pgm_read_word_near(midPWM + servoNum)));
  }
  else {
    pwm.setPWM(servoNum, 0, map(actualAngle, 0, 90, pgm_read_word_near(midPWM + servoNum), pgm_read_word_near(maxPWM + servoNum)));
  }

}

void servoStep() {

  // If still have movements to make
  if (stepsLeft > 0) {

    for (int i = 0; i < NUM_SERVOS; i++) {

      currentAngles[i] = currentAngles[i] + deltas[i];

      // Keep any centred servos limp to save power
      if (abs(currentAngles[i]) > 1 || !SAVE_POWER) {
        setServoAngle(i, currentAngles[i]);
      }
      else {
        pwm.setPWM(i, 0, 0);
      }

    }

    stepsLeft = stepsLeft - 1;

  // Otherwise calculate the new deltas
  } else if (numInQueue > 0) {

    stepsLeft = queue[1];
    for (int i = 0; i < NUM_SERVOS; i++) {
      deltas[i] = (float(pgm_read_word_near(&(positions[queue[0]][i]))) - currentAngles[i]) / float(stepsLeft);
    }

    // Shift the queue along
    for (int i = 0; i < QUEUE_SIZE*2 - 2; i += 2) {

      queue[i] = queue[i + 2];
      queue[i + 1] = queue[i + 3];

    }

    numInQueue = numInQueue - 1;

    if (Serial) {
      Serial.println(F("new deltas:"));
      printFloatArray(deltas, NUM_SERVOS);
      Serial.println(F("new queue (removed):"));
      printIntArray(queue, QUEUE_SIZE * 2);
    }

  }

}

void printIntArray(int toPrint[], int arraySize) {

  for (int i = 0; i < arraySize - 1; i++) {
    Serial.print(toPrint[i]);
    Serial.print(", ");
  }
  Serial.println(toPrint[arraySize - 1]);

}

void printFloatArray(float toPrint[], int arraySize) {

  for (int i = 0; i < arraySize - 1; i++) {
    Serial.print(toPrint[i]);
    Serial.print(", ");
  }
  Serial.println(toPrint[arraySize - 1]);

}

// Add a position to the end of the queue
void addToQueue(int pos, int steps) {

  queue[numInQueue * 2] = pos;
  queue[numInQueue * 2 + 1] = steps;
  numInQueue = numInQueue + 1;

  if (Serial) {
    Serial.println("new queue (added):");
    printIntArray(queue, QUEUE_SIZE * 2);
  }

}

// Retrieves the x/y/z accelerometer data
void getAccelData(float values[]) {

  // Accel data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  values[0] = (Wire.read() << 8 | Wire.read()) / 16384.0;
  values[1] = (Wire.read() << 8 | Wire.read()) / 16384.0;
  values[2] = (Wire.read() << 8 | Wire.read()) / 16384.0;

}

void gatherInfo() {}
void updateActions() {}

void setup() {

  // Setup servo control
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  // Setup serial comms
  if (Serial) {

    Serial.begin(9600);
    while (!Serial);
    Serial.flush();
    Serial.println(F("started"));

  }

  // Setup SD card reading
  if (!SD.begin()) {
    if (Serial) {
      Serial.println(F("ERROR - SD card init failed"));
    }
  }

  // Setup and wake the accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Reset all servos
  for (int i = 0; i < NUM_SERVOS; i++) {

    currentAngles[i] = 0;
    setServoAngle(i, currentAngles[i]);

  }

  delay(100);

  // Limp all servos
  for (int i = 0; i < NUM_SERVOS; i++) {pwm.setPWM(i, 0, 0);}

}

void loop() {

  if (Serial.available() > 0) {

    incomingByte = Serial.read();

    if (int(incomingByte) == 10) {

      if (soFar[0] == '#') {

        newValue = soFar.substring(1).toInt();
        soFar = "";
        Serial.print(F("Setting to position number "));
        Serial.println(newValue);
        addToQueue(newValue, AVG_SPEED);

      } else {

        newValue = soFar.toInt();
        soFar = "";
        Serial.print(F(" to "));
        Serial.println(newValue);
        pwm.setPWM(motorNum, 0, newValue);

      }

    } else if (int(incomingByte) == 32) {

      motorNum = soFar.toInt();
      soFar = "";
      Serial.print(F("Setting motor "));
      Serial.print(motorNum);

    } else {
      soFar = soFar + incomingByte;
    }

  }

  gatherInfo();
  updateActions();
  servoStep();
  delay(5);

}

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SD.h>

#define MPU_ADDR 0x68

// Servo properties
#define SERVO_MIN 205
#define SERVO_MAX 410
#define SERVO_FREQ 50

// Servo pin numbers
#define BACK_LEFT_ANKLE   0
#define BACK_LEFT_KNEE    1
#define BACK_LEFT_HIP     2
#define BACK_RIGHT_ANKLE  3
#define BACK_RIGHT_KNEE   4
#define BACK_RIGHT_HIP    5
#define FRONT_LEFT_ANKLE  6
#define FRONT_LEFT_KNEE   7
#define FRONT_LEFT_HIP    8
#define FRONT_RIGHT_ANKLE 9
#define FRONT_RIGHT_KNEE  10
#define FRONT_RIGHT_HIP   11
#define NECK_VERT         12
#define NECK_HORIZ        13

// Min and max values for each servo, tweak as necessary
const int mins[] = {205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205};
const int maxs[] = {410, 410, 410, 410, 410, 410, 410, 410, 410, 410, 410, 410, 410, 410};

// Main servo controller
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// For testing
File testFile;

// For I/O
String soFar;
int newValue;
int motorNum;
char incomingByte;

// For accelerometer data
float accelData[3];

// Change a servo to an angle between -90 and 90
// TODO 1 change to queue system in main loop
void setServoAngle(uint8_t servoNum, double angle){

  pwm.setPWM(servoNum, 0, map(angle, -90, 90, mins[servoNum], maxs[servoNum]));
    
}

void walkForward(int distance){
  
  
}

void turnOnSpot(int angle){
  
  
}

void getAccelData(float values[]){

  // Accel data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  values[0] = (Wire.read() << 8 | Wire.read()) / 16384.0;
  values[1] = (Wire.read() << 8 | Wire.read()) / 16384.0;
  values[2] = (Wire.read() << 8 | Wire.read()) / 16384.0;

  // Gyro data
  //Wire.beginTransmission(MPU_ADDR);
  //Wire.write(0x43);
  //Wire.endTransmission(false);
  //Wire.requestFrom(MPU_ADDR, 6, true);
  //values[3] = (Wire.read() << 8 | Wire.read()) / 131.0;
  //values[4] = (Wire.read() << 8 | Wire.read()) / 131.0;
  //values[5] = (Wire.read() << 8 | Wire.read()) / 131.0;

}
 
void setup(){

  // Setup servo control
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  Serial.begin(9600);
  Serial.println("started");
  
  Serial.print("SERVO_MIN = ");
  Serial.print(SERVO_MIN);
  Serial.print(", SERVO_MAX = ");
  Serial.println(SERVO_MAX);

  // Setup SD card reading
  if (!SD.begin()) {
    Serial.println("ERROR - SD card init failed, halting");
    while (1);
  }

  if (!SD.remove("test.txt")) {Serial.println("WARNING - couldn't remove test file, new SD card?");}

  // SD card write test
  Serial.println("Testing SD card writing...");
  File writeFile = SD.open("test.txt", FILE_WRITE);
  if (writeFile) {

    writeFile.seek(0);
    writeFile.println("If you're reading this, reading the SD card worked.");
    writeFile.close();
    
  } else {Serial.println("WARNING - couldn't write to SD card");}

  // SD card read test
  Serial.println("Testing SD card reading...");
  File readFile = SD.open("test.txt", FILE_READ);
  if (readFile) {
    
    while (readFile.available()) {Serial.write(readFile.read());}
    readFile.close();
    
  } else {Serial.println("WARNING - couldn't read SD file");}
  
  // Setup the accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Test accelerometer
  getAccelData(accelData);
  Serial.print("aX: "); Serial.print(accelData[0]);
  Serial.print(", aY: "); Serial.print(accelData[1]);
  Serial.print(", aZ: "); Serial.println(accelData[2]);

  // Limp all servos
  for (int i=0; i<1; i++){

    pwm.setPWM(i, 0, 0);
    delay(10);
    
  }

  // Reset all servos initially
  //for (int i=0; i<1; i++){

    //setServoAngle(i, 0);
    //delay(1000);
    //pwm.setPWM(i, 0, 0);
    //delay(1000);
    
  //}
  
}

void loop(){

  if (Serial.available() > 0) {
    
    incomingByte = Serial.read();

    if ((int)incomingByte == 10){

      newValue = soFar.toInt();
      soFar = "";
      Serial.print("Setting to: ");
      Serial.println(newValue);

      pwm.setPWM(motorNum, 0, newValue);

    } else if ((int)incomingByte == 32){

      motorNum = soFar.toInt();
      soFar = "";
      Serial.print("Changing motor: ");
      Serial.println(motorNum);
     
    } else {soFar = soFar + incomingByte;}
    
  }

}

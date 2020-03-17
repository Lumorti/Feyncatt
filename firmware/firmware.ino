#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 120 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 700 // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMID 300 // Middle
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

uint8_t servoNum = 0;

void setup(){

  // Setup serial
  Serial.begin(9600);
  Serial.println("started");

  // Setup servo control
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);

  // Setup SD card reading TODO 1

  delay(10);

  pwm.setPWM(0, 0, SERVOMIN);

  for (int i=0; i<16; i++){

    pwm.setPWM(i, 0, SERVOMIN);
    delay(1000);
    pwm.setPWM(i, 0, SERVOMAX);
    delay(1000);
    pwm.setPWM(i, 0, SERVOMID);
    delay(1000);
    pwm.setPWM(i, 0, 0);
    
  }
  
}

// Change a servo to an angle between -90 and 90
void setServoAngle(uint8_t n, double angle){
  
  
}

void changeToState(){
  
  
}

void loop(){
  

  
}

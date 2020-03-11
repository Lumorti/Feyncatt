#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
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
  
}

void setServoAngle(uint8_t n, double angle){
  
  
}

void changeToState(){
  
  
}

void loop(){
  
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++){
    
    pwm.setPWM(servoNum, 0, pulselen);
    
  }

  delay(500);
  
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--){
    
    pwm.setPWM(servoNum, 0, pulselen);
    
  }

  delay(500);

  servoNum++;
  if (servoNum > 7) servoNum = 0;
  
}

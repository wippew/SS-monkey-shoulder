#include <Servo.h>
#include <SD.h>
#define SD_ChipSelectPin 10
#include <TMRpcm.h>
#include <SPI.h>

TMRpcm sound;
Servo myservo;

int servoPin = 8;

int pos = 0;

int buttonPin = 2;
int buttonState = LOW;

int sol = 7;
int solState = LOW;

//Led
int led1 = 4;
int led2 = 5;


void setup() {
  myservo.attach(servoPin);
  myservo.write(0);
  pinMode(sol, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buttonPin, INPUT);

  sound.speakerPin = 9;
  Serial.begin(9600);
    if (!SD.begin(SD_ChipSelectPin)) {
      Serial.println("SD fail");
      return;
    }

  sound.setVolume(7);
  

  Serial.begin(9600);

}

void cannonsOut() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    myservo.write(pos);
    delay(10);
  }
  delay(1000);
}


void fire() {  

  myservo.detach();
  sound.play("cannon.wav");
  
  digitalWrite(sol, HIGH);  
  delay(100);   
  digitalWrite(sol, LOW);
  
  analogWrite(led1, 255);
  analogWrite(led2, 255);
  
  delay(1000);
  sound.disable();
  myservo.attach(servoPin);
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    delay(15);   
  } 
  analogWrite(led1, 0);
  analogWrite(led2, 0);
  delay(1000);
}


void loop() {
  digitalWrite(sol, LOW);
  
  buttonState = digitalRead(buttonPin);
  solState = digitalRead(sol);
  
  //Serial.println(buttonState);
  Serial.println(buttonState);
  if (true) {  // tests to see if laukaus mode is selected (set on as default for test) buttonState == HIGH
    
    cannonsOut();
  
    delay(1000);
  
    fire();
    
    delay(1000);
   
  }
}

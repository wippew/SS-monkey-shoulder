#include <Servo.h>

Servo myservo;

int servoPin = 9;

int pos = 0;

int buttonPin = 2;
int buttonState = LOW;

int sol = 7;
int solState = LOW;

//Led
int led = 11;


void setup() {
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
  pinMode(sol, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);

}
/*void ledFade(){ // Function for dimming led out after shot. All leds in one circuit.
 
  for(int i = 255; i > 0 ;i-= 5) { // For loop that goes through brightness from 255 to 0 and delays 30 to show the effect. leaves at Brightness = 0
    analogWrite(led, i);
    delay(30);
  }

}*/

void canonsOut() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);
  }
  delay(1000);
}


void fire() {	
  digitalWrite(sol, HIGH);
  delay(100);   
  digitalWrite(sol, LOW);
  
  //ledFade();
  analogWrite(led, 255);
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    //analogWrite(led, pos*(255/180));
    delay(15);
   
  } 
  analogWrite(led, 0);
  delay(1000);
}

void loop() {
  digitalWrite(sol, LOW);
  
  buttonState = digitalRead(buttonPin);
  solState = digitalRead(sol);
  
  //Serial.println(buttonState);
  Serial.println(buttonState);
  if (buttonState == HIGH) {  // tests to see if laukaus mode is selected (set on as default for test)
    
    canonsOut();
  
    delay(1000);
  
    fire();
    
    delay(1000);
   
  }
}

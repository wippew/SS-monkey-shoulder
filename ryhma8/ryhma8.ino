/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

int buttonPin = 2;
int buttonState = LOW;

int sol = 7;
int solState = LOW;

//Led
int led = 11;


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(sol, OUTPUT);
  pinMode(led, OUTPUT);

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);

}
void ledFade(){ // Function for dimming led out after shot. All leds in one circuit.
 
  for(int i = 255; i > 0 ;i-= 1) { // For loop that goes through brightness from 255 to 0 and delays 30 to show the effect. leaves at Brightness = 0
    analogWrite(led, i);
    delay(30);
  }

}

/*void fire(){
  digitalWrite(sol, HIGH);// pushes out the canon(HIGH is the voltage level)
  //ledFade();  // Calls the dimming for ALL leds.
  delay(1000);               // wait for a second
  digitalWrite(sol, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
}*/

void canonsOut() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  delay(1000);
  digitalWrite(sol, HIGH);
  delay(100);   
  digitalWrite(sol, LOW);
  //ledfade()
}

void canonsIn() {
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
   
  } 
}


void loop() {
  digitalWrite(sol, LOW);
  buttonState = digitalRead(buttonPin);
  solState = digitalRead(sol);
  
  //Serial.println(buttonState);
  Serial.println(buttonState);
  if (buttonState == HIGH) {  // tests to see if laukaus mode is selected (set on as default for test)
    
    canonsOut();
  
    delay(10);
  
    canonsIn();
    
    delay(1000); //go for 1 second 
   
  }
}

#include <Servo.h>
#include <SD.h>
#define SD_ChipSelectPin 10 //SD-kortinlukijan käyttämä pin
#include <TMRpcm.h> //ääniefektin soittamiseen käytettävä kirjasto, netistä
#include <SPI.h>

TMRpcm sound;
Servo myservo;

int servoPin = 8;

int pos = 0;

//nappia käytettiin testausvaiheessa
//int buttonPin = 2;
//int buttonState = LOW;

int sol = 7;  //kaikki neljä solenoidia sarjaan kytkettynä yhdessä pinissä
int solState = LOW;

//Ledit kahdessa pinissä molemmissa kaksi lediä sarjaan kytkettynä
int led1 = 4;
int led2 = 5;


void setup() {
  myservo.attach(servoPin);
  myservo.write(0); 
  pinMode(sol, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  //pinMode(buttonPin, INPUT);

  sound.speakerPin = 9;
  Serial.begin(9600);
    if (!SD.begin(SD_ChipSelectPin)) {
      Serial.println("SD fail");  //jos kortti ei ole kiinni, lopeteaan ja ilmoitetaan serial monitorissa
      return;
    }

  sound.setVolume(7); //maksimivolyymi
  

  Serial.begin(9600);

}

void cannonsOut() {
  for (pos = 0; pos <= 180; pos += 1) { // servo pyörii 180 astetta hitaasti
    myservo.write(pos);
    delay(10);
  }
  delay(1000);
}


void fire() {  

  myservo.detach(); //servo- ja TMRpcm-kirjastot eivät pelitä samaan aikaan :(
  sound.play("cannon.wav"); //äänitiedosto sd-kortilta
  
  digitalWrite(sol, HIGH);  
  delay(100);   
  digitalWrite(sol, LOW);
  
  analogWrite(led1, 255);
  analogWrite(led2, 255);
  
  delay(1000);
  
  sound.disable();
  
  myservo.attach(servoPin); //äänen tuottaminen loppui, voidaan taas käyttää servoa
  for (pos = 180; pos >= 0; pos -= 5) { // servo liikkuu 180 astetta taaksepäin, nopeasti
    myservo.write(pos);
    delay(15);   
  } 
  analogWrite(led1, 0); //ledit pois päältä vasta laivan sisällä
  analogWrite(led2, 0);
  delay(1000);
}


void loop() {
  digitalWrite(sol, LOW);
  
  //buttonState = digitalRead(buttonPin);
  solState = digitalRead(sol);
  
  //Serial.println(buttonState);
  Serial.println(buttonState);
  if (true) {  //käytti buttonStatea testausvaiheessa, nyt loopilla niin kauan kuin virta päällä
    
    cannonsOut();
  
    delay(1000);
  
    fire();
    
    delay(1000);
   
  }
}

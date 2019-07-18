#include <SoftwareSerial.h>
#include <Servo.h>

Servo servomoter;
int blueTx=3;
int blueRx=2;   
SoftwareSerial mySerial(blueTx, blueRx);  
String myString="";

int trigPin = 13;
int echoPin = 12;

int motionPin = 8;

int distance = pulseIn(echoPin,HIGH);

int myChar;

void setup() {
  servomoter.attach(9);
  servomoter.write(0);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motionPin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  while(mySerial.available())  {
    myChar = (int)mySerial.read(); 
    delay(5);
  }
  
  if(myChar==1) { 
    servomoter.write(0); 
    digitalWrite(motionPin, LOW); 
  } 
  
  else if(myChar==2) {
    unsigned int duration;
    int distance;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = ((duration/2)/29.1);

    int sensor = digitalRead(motionPin);
    digitalWrite(motionPin, HIGH);
    
    if (distance < 11) {
      Serial.println("TACCA IS FULL!");
      delay(500);
      servomoter.write(0);
      digitalWrite(motionPin, LOW);
    }

    else {
      Serial.print(distance);
      Serial.println(" cm");
      delay(500);
      digitalWrite(motionPin, HIGH);

      if (sensor==HIGH) {
        Serial.println("Human Approaching!");
        delay(500);
        servomoter.write(90);
      }

      else if (sensor==LOW) {
        delay(500);
        servomoter.write(0);
      }
    }
  }
}



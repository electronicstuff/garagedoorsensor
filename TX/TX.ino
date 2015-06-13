// Garage door detector transmitter code
// Twitter @gareth_loader
// Various parts copied from other examples from whom I have forgotten 



#include <VirtualWire.h>
char *SR04;
char *RFLNK;


/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 Red Led = pin 9
 White Led = pin 7
 433mhz Transmitter = pin 5
 */

#define trigPin 10
#define echoPin 12
#define led 9 
#define led2 7

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  vw_set_tx_pin(5);
  vw_setup(4000); //speed of data transfer Kbps
}

void loop() {
  
  
  
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 65) {  // check to see if garage door is within 65cm of the sensor 
  digitalWrite(led,HIGH); // Light the red led to indicate that the garage door is open
  digitalWrite(led2,LOW); 
  SR04="1"; 
  vw_send((uint8_t *)SR04, strlen(SR04)); // send character '1' via the 433mhz link
  vw_wait_tx();
  delay(100);
  
  
  
  
 
}
  else {
    digitalWrite(led,LOW); //set red led to off
    digitalWrite(led2,HIGH); //set white led to high to show that the system is working and the door is closed
    SR04="0"; 
    vw_send((uint8_t *)SR04, strlen(SR04)); // send character '0' via the 433mhz link
    vw_wait_tx();
    delay(100);
  }
  
  // send the reading via serial incase we need them for debugging 
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(100);
}

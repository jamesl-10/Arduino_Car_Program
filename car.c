// Created by: James Lee
// Teacher: Mr. Pewa
// Course: TEJ3M
// Code for automated Arduino car
// Allows car to solve maze

// Declare Servo
// Servo can only be declared on pins 9/10
#include <Servo.h>
Servo servo_9;

// Pins for ultrasound sensor
#define trigPin 10
#define echoPin 13

// Define pins for wheels
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;

// Pins that control motor speed
const int ENA = 3; // pins for motor speed control for both
const int ENB = 8;

// Variables
float duration, distance;
int Forward = 70;
int Left = 160;
int Right = -20;

// Initial function
void setup()
{
  // put your setup code here, to run once:
  Serial.begin (9600);
  delay(1000);
  
  servo_9.attach(9);
  //160 is left
  //70 is forward
  //-20 is right
  servo_9.write(Forward);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ENA,OUTPUT);

  pinMode(ENB,OUTPUT);
}

// Turns left
// Maybe make left turn faster than right?
void turnLeft()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
    delay(200);
    
    stopCar();
}

// Turns right
void turnRight()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(200);
  
  stopCar();
}

// Goes forward
void goForward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void goBackward()
{
  digitalWrite(IN1, LOW);     
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopCar()
{
  digitalWrite(IN1, LOW);     
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void look(int direction)
{
  servo_9.write(direction);
}

int findDistance()
{
  // Code for finding distance in front of sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) * 0.0343;
  
  return distance;
}

// put your main code here, to run repeatedly:
void loop()
{
  // Controls speed of motors
  analogWrite(ENA, 215);
  analogWrite(ENB, 130);
  look(Forward);
  delay(1000);
  int dirForw = findDistance();
  Serial.println(dirForw);

  if (dirForw >= 15) // When there is no obstable in front of car
  {
    goForward();

    delay(300);
    
    stopCar();
    delay(1000);
    
    look(Left);
    delay(500);
    int dL = findDistance();
    Serial.println(dL);

    delay(1000);
    
    look(Right);
    delay(500);
    int dR = findDistance();
    Serial.println(dR);

    delay(1000);

    if (dL > 100 && dR < 20 || dR > 100 && dL < 20)
    {
      //pass
    }
    else if (dL > 100)
    {
      turnLeft();
    }
    
    else if (dR > 100)
    {
      turnRight();
    }
    
    delay(1000);
  }
  
  else //When there is an obstacle in front of car
  {
    stopCar();
    delay(1000);
    goBackward();
    delay(200);
    stopCar();

    delay(1000);

    look(Left);
    delay(1500);
    int distanceLeft = findDistance();
    
    look(Right);
    delay(1500);
    int distanceRight = findDistance();

    if (distanceRight < 15 && distanceLeft < 15)
    {
      // Turn 180
      goBackward();
      delay(200);
      stopCar();
    }
    else if (distanceRight > distanceLeft)
    {
      turnRight();
      delay(100);
    }
    else if (distanceRight < distanceLeft)
    {
      turnLeft();
      delay(100);
    }
    else if (distanceRight == distanceLeft)
    {
      turnLeft();
      delay(100);
    }
  }
}

 // Define pins for sensor
#include <Servo.h>

Servo servo_2;

#define trigPin 10
#define echoPin 13

float duration, distance;

// Define pins for wheels
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;

const int ENA = 3; // pins for motor speed control for both

const int ENB = 9;

String direction = "Forward";

// Initial function
void setup()
{
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin (9600);
  
  servo_2.attach(2);
  //160 is left
  //70 is forward
  //-20 is right
  servo_2.write(70);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ENA,OUTPUT);

  pinMode(ENB,OUTPUT);
}

// Turns left
// Maybe make left turn faster than right
void turnLeft()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// Turns right
void turnRight()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

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

void lookLeft()
{
  servo_2.write(160);
}

void lookRight()
{
  servo_2.write(-20);
}

void lookForward()
{
  servo_2.write(70);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  // Code for finding distance in front of sensor
  analogWrite(ENA, 200);
  analogWrite(ENB, 230);
  Serial.print(direction);
  delay(1000);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) * 0.0343;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  if (distance >= 20)
  {
    if (direction == "Right")
    {
      turnRight();
    }
    if (direction == "Left")
    {
      turnLeft();
    }
    lookForward();
    direction = "Forward";
    goForward();   
  }
  
  else
  {
    if (direction == "Forward")
    {
      lookRight();
      direction = "Right";
    }
    else if (direction == "Right")
    {
      lookLeft();
      direction = "Left";
    }
    else
    {
      goBackward();
      Serial.print("Go back");
    }

    delay(1000);
  }
}

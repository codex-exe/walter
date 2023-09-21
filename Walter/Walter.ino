#include <AFMotor.h>
#include <SoftwareSerial.h>
#define echoPin 7
#define trigPin 6

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

SoftwareSerial bt(0, 1);
long duration;
int distance;
String command;

void setup()
{
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  bt.begin(9600);
  Serial.begin(9600);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
int dist()
{
  digitalWrite(trigPin,LOW);    
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW); 
  duration = pulseIn(echoPin,HIGH);   
  distance = (duration*0.0343)/2;     
  Serial.println(distance);
  delay(250);
  return distance;
}

void avoid()
{
  dist();
  while(dist() < 10)
  {
  Stop(); 
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  delay(500);
  }
  Stop();
}

void forward() 
{
  void avoid();
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  delay(800);
  Stop();
}

void back() 
{
  void avoid();
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  delay(800);
  Stop();
}

void right() 
{
  void avoid();
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  delay(400);
  Stop();
}

void left() 
{
  void avoid();
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  delay(400);
  Stop();
}

void loop() 
{
  dist();
  delay(10);
  while(bt.available()) 
  {
  command = "";  
  command = bt.readString();
  avoid();
  if (command.length() > 0) 
  {
    Serial.print(command);
    if(command == "*move forward#" || command == "*forward#")
    {
      forward();
    }
    else if(command == "*move backward#" || command == "*backward#" || command == "*move back#" || command == "*back#")
    {
      back();
    }
    else if(command == "*turn left#" || command == "*move left#" || command == "*left#")
    {
      left();
    }
    else if(command == "*turn right#" || command == "*move right#" || command == "*right#")
    {
      right();
    }
    else if(command == "*stop#" || command == "*halt#" || command == "*pause#")
    {
      Stop();
    }
    command = "";
  }
  }
}

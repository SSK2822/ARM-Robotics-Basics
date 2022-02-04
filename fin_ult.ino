#include <NewPing.h>

const int trig = 13;
const int echo = 12; // Arduino pin tied to echo pin on the ultrasonic sensor.
const int MAX_DISTANCE = 250; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 250cm.
const int disleft = 30;
const int disright = 30;
const int disfrnt = 15;
NewPing sonar(trig, echo, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing son(A1, A2, 250); 
NewPing sonR(11, 10, 250); 

//boolean goesForward = false;
int distance1 = 0;
int distance2 = 0;
int distance3 = 0;

boolean count = true;

int motor2pin2 = 3 ; //white cable red wire out4
int motor2pin1 = 5 ; //out3
int motor1pin2 = 6;  //out2
int motor1pin1 = 9;  //out1 red wire

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode (motor1pin2, OUTPUT);
  pinMode (motor2pin1, OUTPUT) ;
  pinMode (motor2pin2, OUTPUT) ;
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  distance1 = readPingForward();    // Get Ping Distance.
  delay(10);               // Wait for 100ms.
  distance2 = readPingLeft();
  delay(10);
  distance3 = readPingRight();
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  while(count){
    if(distance1 <= 25){  //&& distance1 !=0
      Serial.println("Front Blocked, Turning Right // First right");
      moveStop();
      delay(200);
      moveBackward();
      delay(150);
      moveStop();
      delay(1000);
      turnRight();    // turnLeft() if starting from other end
      delay(450);
      moveStop();
      delay(100);
      moveForward();
      delay(180);
      count = false;
    }else{
      Serial.println(count);
      Serial.println("Front not blocked // no obstacle yet");
      distance1 = readPingForward();    // Get Ping Distance
      delay(10);
      moveForward();
      delay(20);
    }
  }

  distance1 = readPingForward();    // Get Ping Distance.
  delay(10);              
  distance2 = readPingLeft();
  delay(10);
  distance3 = readPingRight();
  delay(10); 

  Serial.println(distance1);
  Serial.println(distance2);
  Serial.println(distance3);

  if (distance1 < disfrnt && distance2 < disleft && distance3 < disright){
    Serial.println("obstacle on all sides");//obstacle on all sides
    moveStop();
    delay(100);    
    turnRight();
    delay(3000); 
  }
  else if (distance1 < disfrnt && distance2 < disleft && distance3 > disright){
    // obstacle on front and left
    Serial.println("obstacle nit in right, turning right");
    moveStop();
    delay(100);
    turnRight();
    delay(400);
  }
  else if (distance1 < disfrnt && distance2 > disleft && distance3 < disright){
    // obstacle on front and right
    Serial.println("obstacle nit in leftt, turning leftt");
    moveStop();
    delay(100);
    turnLeft();
    delay(400);
  }
  else if (distance1 < disfrnt && distance2 > distance3){ //&& distance2 > disleft && distance3 > disright
    // obstacle on front
    Serial.println("obstacle nit in left and right, turning right");
    moveStop();
    delay(100);
    moveBackward();
    delay(100);
    moveStop();
    delay(100);
    turnLeft();
    delay(400);
//    moveBackward();
//    delay(100);
    
  }
  else if (distance1 < disfrnt && distance2 < distance3){ //&& distance2 > disleft && distance3 > disright
    // obstacle on front
    Serial.println("obstacle nit in left and right, turning right");
    moveStop();
    delay(100);
    moveBackward();
    delay(100);
    moveStop();
    delay(100);
    turnRight();
    delay(400);
//    moveBackward();
//    delay(100);
    
  }
  else if (distance1 > disfrnt && distance2 > disleft && distance3 < disright){
    // obstacle on right
    Serial.println("obstacle nit in left, moving forward turning left");

    moveStop();
    delay(100);
    moveBackward();
    delay(100);
    moveStop();
    turnLeft();
    delay(400);

    moveForward();
    delay(20);
  }
  else if (distance1 > disfrnt && distance2 < disleft && distance3 > disright){
    // obstacle on left
    Serial.println("obstacle nit in right, moving forward and turning right");
    moveStop();
    delay(100);
    moveBackward();
    delay(100);
    moveStop();
//    moveForward();
//    delay(20);
    turnRight();
    delay(400);
    moveForward();
    delay(20);
  }
  else{
    moveForward();
    delay(20);
  }
}


int readPingForward()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(30);                 
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  return cm;
}

int readPingLeft()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(30);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = son.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  return cm;
}

int readPingRight()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(30);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonR.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  return cm;
}

void moveStop()       // Move Stop Function for Motor Driver.
{
  analogWrite (motor1pin1, 0);
  analogWrite(motor1pin2, 0);
  analogWrite(motor2pin2, 0);
  analogWrite(motor2pin1, 0);
}

void moveForward()    // Move Forward Function for Motor Driver.
{
  analogWrite(motor1pin1, 50);
  analogWrite(motor1pin2, 0);   //analog
  analogWrite(motor2pin1, 50);
  analogWrite(motor2pin2, 0);
}

void moveBackward()   // Move Backward Function for Motor Driver.
{
  analogWrite (motor2pin2, 70);
  analogWrite(motor2pin1, 0);
  analogWrite(motor1pin2, 70);  //analog
  analogWrite(motor1pin1, 0);
}

void turnLeft()      // Turn Right Function for Motor Driver.
{
  analogWrite (motor2pin1, 0);
  analogWrite(motor2pin2, 0);
  analogWrite(motor1pin2, 0);
  analogWrite(motor1pin1, 200);
}

void turnRight()       // Turn Left Function for Motor Driver.
{
  analogWrite (motor1pin1, 0);
  analogWrite(motor1pin2, 0);   //analog
  analogWrite(motor2pin2, 0);
  analogWrite(motor2pin1, 200);
}

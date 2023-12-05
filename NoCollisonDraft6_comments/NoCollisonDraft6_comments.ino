#include <Servo.h>
// Include the Servo library for controlling the servo motor.

Servo myservo;
// Create a Servo object named myservo to control the servo motor.

int PWMA = 5;
int AIN1 = 7; // Direction motor B
int BIN1 = 8; // Direction motor A
int PWMB = 6;
int STBY = 3;
// Define pin numbers for motor control and standby.

int MINspeed = 50;
int SPEED1 = 100;
int SPEED2 = 150;
int SPEED3 = 200;
// Define speed values for different motor speeds.

int MAXspeed = 255;
// Define the maximum motor speed.

int oneEighty = 648; // amount of milliseconds to go 180 degrees when going right
// Define the time required to turn 180 degrees.

int maxDis = 60;
// Define the maximum distance for obstacle detection.

#define trigPin 13
#define echoPin 12
int servoSig = 10;
// Define pin numbers for ultrasonic sensor trigger, echo, and servo signal.

void forward(int speed) {
  // Define a function to make the car move forward with a specified speed.
  stop(); // Stop the car before moving the servo
  digitalWrite(STBY, 1);

  // motor A
  pinMode(PWMA, OUTPUT);       // Set PWMA pin as OUTPUT
  analogWrite(PWMA, speed);    // Set the speed of motor A using PWM
  pinMode(AIN1, OUTPUT);       // Set AIN1 pin as OUTPUT
  digitalWrite(AIN1, 1);      // Set the direction of motor A (1 for forward)

  // Motor B
  pinMode(PWMB, OUTPUT);       // Set PWMB pin as OUTPUT
  analogWrite(PWMB, speed);    // Set the speed of motor B using PWM
  pinMode(BIN1, OUTPUT);       // Set BIN1 pin as OUTPUT
  digitalWrite(BIN1, 1);      // Set the direction of motor B (1 for forward)
}


// (Similar comments apply to the following functions: left, right, backward, stop)

void stop() {
  // Define a function to stop the car.
  digitalWrite(STBY, 1);

  // motor A
  pinMode(PWMA, OUTPUT);
  analogWrite(PWMA, 0);
  pinMode(AIN1, OUTPUT);
  digitalWrite(AIN1, 1);

  // Motor B
  pinMode(PWMB, OUTPUT);
  analogWrite(PWMB, 0);
  pinMode(BIN1, OUTPUT);
  digitalWrite(BIN1, 1);
}

void servoMiddle() { myservo.write(90); }
// Set the servo to the middle position.

void servoRight() {
  stop(); // Stop the car before moving the servo
  myservo.write(0);
}
// Set the servo to the right position.

void servoLeft() {
  stop(); // Stop the car before moving the servo
  myservo.write(180);
}
// Set the servo to the left position.

int Distance_Read() {
  // Define a function to measure the distance using the ultrasonic sensor.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2) * 0.0343;
  return (int)distance;
}

void setup() {
  // Set up the initial configuration.
  myservo.attach(servoSig);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // The main loop of the program.

  servoMiddle(); // Start with the servo in the middle position
  delay(500);    // Wait for the servo to settle

  int middleDistance = Distance_Read();
  int rightDistance, leftDistance;

  Serial.println(middleDistance);

  if (middleDistance <= maxDis) {
    // Obstacle detected in the middle, turn servo to the right
    servoRight();
    delay(500); // Wait for the servo to move
    rightDistance = Distance_Read();

    if (rightDistance <= maxDis) {
      // Obstacle still detected to the right, turn servo to the left
      servoLeft();
      delay(500); // Wait for the servo to move
      leftDistance = Distance_Read();

      if (leftDistance <= maxDis) {
        // Obstacle still detected to the left, move backward for two seconds
        backward(SPEED2);
        delay(1000);
        right(SPEED1);
        delay(oneEighty);
      } else {
        // No obstacle to the left, move the car to the left
        left(SPEED2);
        
      }
    } else {
      // No obstacle to the right, move the car to the right
      right(SPEED2);
     
    }
  } else {
    // No obstacle in the middle, move the car forward at SPEED2
    forward(SPEED2);
    
  }
}


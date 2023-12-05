#include <Servo.h>

Servo myservo;
int PWMA = 5;
int AIN1 = 7; // Direction motor B
int BIN1 = 8; // Direction motor A
int PWMB = 6;
int STBY = 3;

int MINspeed = 50;
int SPEED1 = 100;
int SPEED2 = 150;
int SPEED3 = 200;

int MAXspeed = 255;

int oneEighty = 648; // amount of milliseconds to go 180 degrees when going right

int maxDis = 60;

#define trigPin 13
#define echoPin 12
int servoSig = 10;

void forward(int speed) {
  stop(); // Stop the car before moving the servo
  digitalWrite(STBY, 1);

  // motor A
  pinMode(PWMA, OUTPUT);
  analogWrite(PWMA, speed);
  pinMode(AIN1, OUTPUT);
  digitalWrite(AIN1, 1);

  // Motor B
  pinMode(PWMB, OUTPUT);
  analogWrite(PWMB, speed);
  pinMode(BIN1, OUTPUT);
  digitalWrite(BIN1, 1);
}

void left(int speed) {
  stop(); // Stop the car before moving the servo
  digitalWrite(STBY, 1);

  // motor A
  pinMode(PWMA, OUTPUT);
  analogWrite(PWMA, speed);
  pinMode(AIN1, OUTPUT);
  digitalWrite(AIN1, 1);

  // Motor B
  pinMode(PWMB, OUTPUT);
  analogWrite(PWMB, speed);
  pinMode(BIN1, OUTPUT);
  digitalWrite(BIN1, 0);
}

void right(int speed) {
  stop(); // Stop the car before moving the servo
  digitalWrite(STBY, 1);

  // motor A
  pinMode(PWMA, OUTPUT);
  analogWrite(PWMA, speed);
  pinMode(AIN1, OUTPUT);
  digitalWrite(AIN1, 0);

  // Motor B
  pinMode(PWMB, OUTPUT);
  analogWrite(PWMB, speed);
  pinMode(BIN1, OUTPUT);
  digitalWrite(BIN1, 1);
}

void backward(int speed) {
  stop(); // Stop the car before moving the servo
  digitalWrite(STBY, 1);

  // motor A
  pinMode(PWMA, OUTPUT);
  analogWrite(PWMA, speed);
  pinMode(AIN1, OUTPUT);
  digitalWrite(AIN1, 0);

  // Motor B
  pinMode(PWMB, OUTPUT);
  analogWrite(PWMB, speed);
  pinMode(BIN1, OUTPUT);
  digitalWrite(BIN1, 0);
}

void stop() {
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

void servoRight() {
  stop(); // Stop the car before moving the servo
  myservo.write(0);
}

void servoLeft() {
  stop(); // Stop the car before moving the servo
  myservo.write(180);
}

int Distance_test() {
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
  myservo.attach(servoSig);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  servoMiddle(); // Start with the servo in the middle position
  delay(500);    // Wait for the servo to settle

  int middleDistance = Distance_test();
  int rightDistance, leftDistance;

  Serial.println(middleDistance);

  if (middleDistance <= maxDis) {
    // Obstacle detected in the middle, turn servo to the right
    servoRight();
    delay(500); // Wait for the servo to move
    rightDistance = Distance_test();

    if (rightDistance <= maxDis) {
      // Obstacle still detected to the right, turn servo to the left
      servoLeft();
      delay(500); // Wait for the servo to move
      leftDistance = Distance_test();

      if (leftDistance <= maxDis) {
        // Obstacle still detected to the left, move backward for two seconds
        backward(SPEED2);
        delay(1000);
        right(SPEED1);
        delay(oneEighty);
      } else {
        // No obstacle to the left, move the car to the left
        left(SPEED2);
        return;
      }
    } else {
      // No obstacle to the right, move the car to the right
      right(SPEED2);
      return;
    }
  } else {
    // No obstacle in the middle, move the car forward at SPEED2
    forward(SPEED2);
    return;
  }
}
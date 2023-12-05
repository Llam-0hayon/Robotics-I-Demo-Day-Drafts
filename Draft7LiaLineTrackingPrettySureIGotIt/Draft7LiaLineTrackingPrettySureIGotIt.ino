       

const int pinLeft = A2;
const int pinMiddle = A1;
const int pinRight = A0;

int lineDetectMin = 250;// these values can vhange depending on brightnees of room DARKER the room LOWER the values
int lineDetectMax = 850;// these values can vhange depending on brightnees of room DARKER the room LOWER the values

int detectNotOnGround =910;// these values can vhange depending on brightnees of room DARKER the room LOWER the values

int PWMA =5;
int AIN1=7; // Direction motor B
int BIN1=8;// Direction motor A
int PWMB =6;
int STBY =3;

int MINspeed = 50;// MINImum speed before car or atleast my car struggles

int SPEED1 = 100; //MINspeed for MOVING   TURNS

int SPEED2 = 150;
int SPEED3 = 200;

int MAXspeed = 255;// MAXimum speed before car or atleast my car struggles

void forward(int speed){

  digitalWrite(STBY,1);

  //motor A
  pinMode(PWMA,OUTPUT);
  analogWrite (PWMA,speed);
  pinMode(AIN1,OUTPUT);
  digitalWrite (AIN1,1);

  //Motor B
  pinMode(PWMB,OUTPUT);
  analogWrite(PWMB, speed);
  pinMode(BIN1,OUTPUT);
  digitalWrite (BIN1,1);
    
 
} 

void left(int speed){ // Left means it just turns left meaning stop moving forward and just moves in places leftward or counterclockwise for aslong as delaspeed dictates

  digitalWrite(STBY,1);

  //motor A
  pinMode(PWMA,OUTPUT);
  analogWrite (PWMA,speed);
  pinMode(AIN1,OUTPUT);
  digitalWrite (AIN1,1);

  //Motor B
  pinMode(PWMB,OUTPUT);
  analogWrite(PWMB, speed);
  pinMode(BIN1,OUTPUT);
  digitalWrite (BIN1,0);
}

void right(int speed){  //Right means it just turns right meaning stop moving forward and just moves in places rightward  or clockwise for aslong as delaspeed dictates

  digitalWrite(STBY,1);

  //motor A
  pinMode(PWMA,OUTPUT);
  analogWrite (PWMA,speed);
  pinMode(AIN1,OUTPUT);
  digitalWrite (AIN1,0);

  //Motor B
  pinMode(PWMB,OUTPUT);
  analogWrite(PWMB, speed);
  pinMode(BIN1,OUTPUT);
  digitalWrite (BIN1,1);

  

}  

void stop (){  

  digitalWrite(STBY,1);

  //motor A
  pinMode(PWMA,OUTPUT);
  analogWrite (PWMA,0);
  pinMode(AIN1,OUTPUT);
  digitalWrite (AIN1,1);

  //Motor B
  pinMode(PWMB,OUTPUT);
  analogWrite(PWMB, 0);
  pinMode(BIN1,OUTPUT);
  digitalWrite (BIN1,1);
 
  

}

unsigned long noLineStartTime = 0;  // Variable to store the start time for noLine function

void noLine() {
  unsigned long currentTime = millis();

  if (currentTime - noLineStartTime < 200) {
    // 0~200ms: Turn right
    right(100);
  } else if (currentTime - noLineStartTime < 1600) {
    // 200~1600ms: Turn left
    left(100);
  } else if (currentTime - noLineStartTime < 3000) {
    // 1600~3000ms: Turn right
    right(100);
    Serial.print("\t");
    Serial.println("Turn Right");
  } else if (currentTime - noLineStartTime < 3500) {
    // 3000~3500ms: Stop
    stop();
    Serial.print("\t");
    Serial.println("Stop");
  } else {
    // Reset the start time for the next iteration
    noLineStartTime = currentTime;
  }
}


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
pinMode(pinLeft,INPUT);
pinMode(pinMiddle, INPUT);
pinMode(pinRight, INPUT);

}


void loop() {
  // put your main code here, to run repeatedly:
  int leftPinRead = analogRead(pinLeft);
  int middlePinRead = analogRead(pinMiddle);
  int rightPinRead = analogRead(pinRight);

  if (leftPinRead > detectNotOnGround && middlePinRead > detectNotOnGround && rightPinRead > detectNotOnGround) {
    stop();
    Serial.print("\t");
    Serial.println("NOT On Ground");
  } else if (lineDetectMin <= middlePinRead && middlePinRead <= lineDetectMax) {
    forward(100);
    Serial.print("\t");
    Serial.println("Go Straight");
  } else if (lineDetectMin <= leftPinRead && leftPinRead <= lineDetectMax ) {
    left(100);
    Serial.print("\t");
    Serial.println("Turn Left");
  } else if (lineDetectMin <= rightPinRead && rightPinRead <= lineDetectMax) {
    right(100);
    Serial.print("\t");
    Serial.println("Turn Right");
  } else {
    noLine();
    Serial.print("\t");
    Serial.println("NO LINE");
  }

  Serial.print("\t");
  Serial.print("Analog Reading Left=");
  Serial.print(leftPinRead);
  Serial.print("\t Analog Reading Middle=");
  Serial.print(middlePinRead);
  Serial.print("\t Analog Reading Right=");
  Serial.println(rightPinRead);

  delay(1000);
}

#include <IRremote.h>
// Define the IR receiver pin
const int IR_PIN = 9;
// Define the IR receiver object
IRrecv irrecv(IR_PIN);

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

int oneEighty = 648; // amount of milliseconds to go 180 deggres when going right

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

void backward(int speed){

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
  digitalWrite (BIN1,0);
    
 
} 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
}
void loop() {
  // Check if there are any available codes in the buffer
  if (irrecv.decode()) {
    // Print the HEX value of the button press
    unsigned long receivedCode = irrecv.decodedIRData.decodedRawData;
    Serial.println(receivedCode);

    // Define the codes as variables
    const unsigned long stopCode = 3208707840;        //OK button
    const unsigned long backwardCode = 3927310080;    //BACWARD arrow button
    const unsigned long forwardCode = 3108437760;     //FORWARD arrow button
    const unsigned long leftCode = 3141861120;        //LEFT arrow button
    const unsigned long rightCode = 3158572800;       //RIGHT arrow button

    // Check if the received code matches the stop code
    if (receivedCode == stopCode) {
      stop(); // Stop the motors when the stop code is received
    }

    // Check if the received code matches the backward code
    else if (receivedCode == backwardCode) {
      backward(100); // Execute backward function with a speed of 100
    }

    // Check if the received code matches the forward code
    else if (receivedCode == forwardCode) {
      forward(100); // Move forward with a speed of 100
    }

    // Check if the received code matches the left code
    else if (receivedCode == leftCode) {
      left(100); // Turn left with a speed of 100
    }

    // Check if the received code matches the right code
    else if (receivedCode == rightCode) {
      right(100); // Turn right with a speed of 100
    }

    // Reset the IR receiver for the next signal
    irrecv.resume();
  }

  // Continue with other non-blocking tasks in the loop
}


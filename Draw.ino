#include <Servo.h>
#include <AFMotor.h>

// Writing Servo
Servo pencilServo;
int pencilServoPin = 21;  
// servo positions to move pencil up and down
// higher number is up
int pencilUp = 113, pencilDown = 98;

// Stepper Motors
AF_Stepper linear(48, 1);
AF_Stepper base(48, 2);

// LED Pin
int ledProgress = 22, ledSensor = 24;

// Button pins
int buttons[] = {30, 31, 32, 33, 34};

int pot = 8;
int temp = 9;
int photo = 10;

// position that linear axis has travelled
int pos = 0;

bool state = true;

// true is up (higher #)
// false is down (lower #)  
void movePencil(bool state) {
    if (state)
        pencilServo.write(pencilUp);
    else
        pencilServo.write(pencilDown);
      
}

void circle(String dir = "FORWARD") {
  if (dir == "BACKWARD") 
    base.step(240, BACKWARD, SINGLE);
  else
    base.step(240, FORWARD, SINGLE);
}

void side(int steps) {
  pos += steps;
  if (steps < 0) {
    linear.step(-steps, BACKWARD, DOUBLE);
  }
  else {
    linear.step(steps, FORWARD, DOUBLE);
  }
//  linear.release();
//  delay(5000);
}

void center() {
  side(-pos);
//  linear.step(-pos, FORWARD, DOUBLE); 
  pos = 0;
}

void stopAll() {
    movePencil(true);
    center();
    linear.release();
    base.release();
}

// draw many circles
// button 2
void manyCircles() {
  movePencil(true);
//  center();
  int increments = 100, circles = 5;
  for (int i = 0; i < circles; i++) {
    movePencil(true);
    side(increments);
    movePencil(false);
    delay(50);
    circle();
    delay(100);
  }
  movePencil(true);
  center();
}

void tempCircles() {
  movePencil(true);
  int increments = 100, circles = 5;
  for (int i = 0; i < circles; i++) {
    movePencil(true);
    side(increments);
    movePencil(false);
    delay(50);
    auto dir = "FORWARD";
    if (analogRead(temp) > 700) {
      dir = "BACKWARD";
    }
    circle(dir);
    delay(100);
  }  
}

void photoCircles() {
  int increments, circles = 5;
  for (int i = 0; i < circles; i++) {
    increments = map(analogRead(photo), 0, 1024, 50, 150);
    movePencil(true);
    side(increments);
    movePencil(false);
    delay(50);
    circle();
    delay(100);
  }
  movePencil(true);
  center();
}

// button 3
void spiralSensor() {
  int prevRead = analogRead(pot);
  int potRead = prevRead;
  while (true) {
    if (digitalRead(buttons[0]) == HIGH) {
      stopAll();
      return;
    }
    
    potRead = analogRead(pot);
    if (prevRead != potRead) {
      prevRead = potRead;
    }
    else {
      potRead = 0;
    }
    potRead = map(potRead, 0, 1024, -5, 5);
    base.step(3, FORWARD, DOUBLE);
    linear.step(potRead, FORWARD, MICROSTEP);
  }
}

// button 4
void spiral() {
  for (int i = 0; i < 35; i++) {
    base.step(3, FORWARD, DOUBLE);
    linear.step(30, FORWARD, MICROSTEP);
    delay(10);
    delay(10);
    delay(10);
  }
}

// button 5

void setup() {
    Serial.begin(9600);
    
    pencilServo.attach(pencilServoPin);

    linear.setSpeed(300);
    linear.release();

    base.setSpeed(300);
    base.release();

    // buttons
    for (int i = 0; i < 5; i++) {
      pinMode(buttons[i], INPUT_PULLUP);
    }
    // led
    pinMode(ledProgress, OUTPUT);
    pinMode(ledSensor, OUTPUT);
    movePencil(false);
}   

void loop() {
  
    if (digitalRead(buttons[0] == LOW)) {
      stopAll();
    }

    else if (digitalRead(buttons[1] == LOW)) {
      digitalWrite(ledProgress, HIGH);
      side(200);
      digitalWrite(ledProgress, LOW);
    }

    else if (digitalRead(buttons[2] == LOW)) {
      digitalWrite(ledProgress, HIGH);
      manyCircles();
      digitalWrite(ledProgress, LOW);
    }

    else if (digitalRead(buttons[3] == LOW)) {
      digitalWrite(ledSensor, HIGH);
      digitalWrite(ledProgress, LOW);
      delay(200);
      bool action = true;
      while(digitalRead(buttons[3]) != LOW && action) {
        if (buttons[0] == LOW) {
         action = false; 
         digitalWrite(ledProgress, HIGH);
         spiralSensor();
        }
        else if (buttons[1] == LOW) {
          action = false;
          digitalWrite(ledProgress, HIGH);
          photoCircles();
        }
        else if (buttons[2] == LOW) {
          action = false;
          digitalWrite(ledProgress, HIGH);
          tempCircles();
        }
      }
      stopAll();
    }
    digitalWrite(ledSensor, LOW);
    digitalWrite(ledProgress, LOW);
    
//    linear.step(400, FORWARD, DOUBLE);
//    base.step(200, FORWARD, SINGLE);

//  circle();
//manyCircles();
//side(-400);
//linear.step(400, FORWARD, DOUBLE);
//side(200);
//delay(1000);
//linear.step(400, BACKWARD, DOUBLE);
//movePencil(false);
//side(800);
//delay(1000);
//side(-200);
//delay(3000);
//delay(3000);
//side(-800);
//delay(3000);
//    base.step(400, FORWARD, DOUBLE);
//    delay(1000);
//    linear.release();
//    delay(1000);
//  delay(750);
//  movePencil(state);
//  state = !state;
//  delay(1000);
//  for (int i = 0; i < 40; i++) {
//    linear.onestep(FORWARD, DOUBLE);
//  }
//  for (int i = 0; i < 100; i++) {
//    base.onestep(FORWARD, DOUBLE);
//  }
//movePencil(false);
//delay(1000);
//  spiral();
//  base.step(10, FORWARD, SINGLE);
//  linear.step(150, BACKWARD, DOUBLE);
} 

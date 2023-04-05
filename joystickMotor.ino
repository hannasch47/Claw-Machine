#include <Servo.h>

#define joyX A1
#define joyY A0
#define button 10

double xValue;
double yValue;

#define xmin 0
#define xmax 50
#define ymin 0
#define ymax 50

int xpos;
int ypos;
int xsteps;
int ysteps;

// Define stepper motor connections and steps per revolution:
// A has to be pins 12 and 13
#define XstepPin 2
#define XdirPin 5
#define AstepPin 12
#define AdirPin 13
#define YstepPin 3
#define YdirPin 6
#define ZstepPin 4
#define ZdirPin 7
#define stepsPerRevolution 10

Servo myServo;

void setup() {
  pinMode(button, INPUT_PULLUP);

  myServo.write(180);
  
  xpos = 0;
  ypos = 0;
  
  Serial.begin(9600);
  // Declare pins as output:
  pinMode(XstepPin, OUTPUT);
  pinMode(XdirPin, OUTPUT);
  pinMode(AstepPin, OUTPUT);
  pinMode(AdirPin, OUTPUT);
  pinMode(YstepPin, OUTPUT);
  pinMode(YdirPin, OUTPUT);
  pinMode(ZstepPin, OUTPUT);
  pinMode(ZdirPin, OUTPUT);
  pinMode(8,OUTPUT);

  myServo.attach(9);
  
  digitalWrite(XstepPin, LOW);
  digitalWrite(AstepPin, LOW);
  digitalWrite(YstepPin, LOW);
  digitalWrite(ZstepPin, LOW);
}
 
void loop() {
  while(digitalRead(button))
  {
      // put your main code here, to run repeatedly:
      xValue = analogRead(joyX);
    //  Serial.print(xValue);
      yValue = analogRead(joyY);
    //  Serial.print(yValue);
     
      if(xValue > 800 && !(yValue < 50) && !(yValue > 800) && xpos < xmax)
      {
    //    Serial.print("right");
        digitalWrite(XdirPin, LOW);
        digitalWrite(AdirPin, HIGH);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          // These four lines result in 1 step:
          digitalWrite(XstepPin, HIGH);
          digitalWrite(AstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(XstepPin, LOW);
          digitalWrite(AstepPin, LOW);
          delayMicroseconds(2000);
          }
        xpos++;
      }
      else if(xValue < 50 && !(yValue < 50) && !(yValue > 800) && xpos > xmin)
      {
    //    Serial.print("left");
        digitalWrite(XdirPin, HIGH);
        digitalWrite(AdirPin, LOW);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          digitalWrite(XstepPin, HIGH);
          digitalWrite(AstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(XstepPin, LOW);
          digitalWrite(AstepPin, LOW);
          delayMicroseconds(2000);
          }
        xpos--;
      }
      else if(xValue < 50 && yValue < 50 && xpos > xmin && ypos > ymin)
      {
    //    Serial.print("left up");
        digitalWrite(XdirPin, HIGH);
        digitalWrite(AdirPin, LOW);
        digitalWrite(YdirPin, LOW);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          // These four lines result in 1 step:
          digitalWrite(XstepPin, HIGH);
          digitalWrite(AstepPin, HIGH);
          digitalWrite(YstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(XstepPin, LOW);
          digitalWrite(AstepPin, LOW);
          digitalWrite(YstepPin, LOW);
          delayMicroseconds(2000);
          }
        xpos--;
        ypos--;
      }
      else if(xValue > 800 && yValue > 800 && xpos < xmax && ypos < ymax)
      {
    //    Serial.print("left down");
        digitalWrite(XdirPin, LOW);
        digitalWrite(AdirPin, HIGH);
        digitalWrite(YdirPin, HIGH);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          digitalWrite(XstepPin, HIGH);
          digitalWrite(AstepPin, HIGH);
          digitalWrite(YstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(XstepPin, LOW);
          digitalWrite(AstepPin, LOW);
          digitalWrite(YstepPin, LOW);
          delayMicroseconds(2000);
          }
        xpos++;
        ypos++;
      }
      else if(yValue > 800 && !(xValue < 50) && !(xValue > 800) && ypos < ymax)
      {
    //    Serial.print("down");
        digitalWrite(YdirPin, HIGH);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          // These four lines result in 1 step:
          digitalWrite(YstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(YstepPin, LOW);
          delayMicroseconds(2000);
          }
        ypos++;
      }
      else if(yValue < 50 && !(xValue < 50) && !(xValue > 800) && ypos > ymin)
      {
    //    Serial.print("up");
        digitalWrite(YdirPin, LOW);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          // These four lines result in 1 step:
          digitalWrite(YstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(YstepPin, LOW);
          delayMicroseconds(2000);
          }
        ypos--;
      }
      else if(yValue > 800 && xValue < 50 && ypos < ymax && xpos > xmin)
      {
    //    Serial.print("down");
        digitalWrite(YdirPin, HIGH);
        digitalWrite(XdirPin, HIGH);
        digitalWrite(AdirPin, LOW);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          // These four lines result in 1 step:
          digitalWrite(YstepPin, HIGH);
          digitalWrite(XstepPin, HIGH);
          digitalWrite(AstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(XstepPin, LOW);
          digitalWrite(AstepPin, LOW);
          digitalWrite(YstepPin, LOW);
          delayMicroseconds(2000);
          }
        ypos++;
        xpos--;
      }
      else if(yValue < 50 && xValue > 800 && ypos > ymin && xpos < xmax)
      {
    //    Serial.print("up");
        digitalWrite(YdirPin, LOW);
        digitalWrite(XdirPin, LOW);
        digitalWrite(AdirPin, HIGH);
        for (int i = 0; i < stepsPerRevolution; i++) 
          {
          // These four lines result in 1 step:
          digitalWrite(YstepPin, HIGH);
          digitalWrite(XstepPin, HIGH);
          digitalWrite(AstepPin, HIGH);
          delayMicroseconds(2);
          digitalWrite(XstepPin, LOW);
          digitalWrite(AstepPin, LOW);
          digitalWrite(YstepPin, LOW);
          delayMicroseconds(2000);
          }
        ypos--;
        xpos++;
      }
  }

  //Move the claw down
  digitalWrite(ZdirPin, LOW);
  for (int i = 0; i < 45 * stepsPerRevolution; i++) {
    digitalWrite(ZstepPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(ZstepPin, LOW);
    delayMicroseconds(2200);
    }

//  Close the claw
  for (int a = 180; a >= 120; a = a - 3)
  {
    myServo.write(a);
    delay(35);
  }

  //Move the claw up
  digitalWrite(ZdirPin, HIGH);
  for (int i = 0; i < 45 * stepsPerRevolution; i++) {
    digitalWrite(ZstepPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(ZstepPin, LOW);
    delayMicroseconds(2200);
    }

//  Open the claw
  for (int a = 120; a <= 180; a = a + 3)
   {
     myServo.write(a);
     delay(35);
   }


//returning back to zero
  digitalWrite(XdirPin, HIGH);
  digitalWrite(AdirPin, LOW); 
  digitalWrite(YdirPin, LOW);

  //moving along diaganol first
  if (xpos > ypos){
    xsteps = xpos / ypos;
    ysteps = 1;
   }
   else{
    ysteps = ypos / xpos;
    xsteps = 1;
   }
   
   int num = min(ypos / ysteps, xpos / xsteps);
   for(int i = 0; i < num; i++){
    for(int j = 0; j < stepsPerRevolution * xsteps; j++){
      digitalWrite(XstepPin, HIGH);
      digitalWrite(AstepPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(XstepPin, LOW);
      digitalWrite(AstepPin, LOW);
      delayMicroseconds(2000);
    }
    xpos = xpos - xsteps;
    for(int k = 0; k < stepsPerRevolution * ysteps; k++){
      digitalWrite(YstepPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(YstepPin, LOW);
      delayMicroseconds(2000);
    }
    ypos = ypos - ysteps;
   }

//return rest of the way to 0   
    //return x to 0 
    while (xpos != 0) {
      for (int i = 0; i < stepsPerRevolution; i++) {
      digitalWrite(XstepPin, HIGH);
      digitalWrite(AstepPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(XstepPin, LOW);
      digitalWrite(AstepPin, LOW);
      delayMicroseconds(2000);
      }
      xpos--;
    }
  
    while (ypos != 0) {
      for (int i = 0; i < stepsPerRevolution; i++) {
      digitalWrite(YstepPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(YstepPin, LOW);
      delayMicroseconds(2000);
      }
      ypos--;
    }
  
}

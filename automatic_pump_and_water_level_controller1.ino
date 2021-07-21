#include <LiquidCrystal.h>
#define lenght 16.0
#include <Servo.h>

double percent=100.0;
unsigned char b;
unsigned int peace;
int distanceTreshold = 0;
int cm = 0;
int buttonstate = 0;
int count = 0;

Servo servo_9;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte p1[8] = {
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10};
byte p2[8] = {
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18};
byte p3[8] = {
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C};
byte p4[8] = {
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E};
byte p5[8] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F};


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(6, INPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);
  lcd.begin(16, 2);
  digitalWrite(10, HIGH);
  digitalWrite(13, LOW);
}

void loop()
{
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  buttonstate = digitalRead(6);
  distanceTreshold = 336;
  percent = (cm/336.0)*100.0;
  
  if (buttonstate == HIGH){
    digitalWrite(10, LOW);
    digitalWrite(13, HIGH);
    servo_9.attach(9);
    count++;
    if (count == 1){
      delay(100);
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print("POWER ON");
      lcd.setCursor(0, 1);
      lcd.print("VALVE & PUMP");
      delay(100);
    }
    if (cm > distanceTreshold-168) {
      if (count ==1){
        delay(1000);
      }
      servo_9.write(90);
      if (count ==1){
        delay(1000);
      }
      digitalWrite(8, HIGH);
    }
    if (cm < distanceTreshold-319) {
      if (count ==1){
        delay(1000);
      }
      digitalWrite(8, LOW);
      if (count ==1){
        delay(1000);
      }
      servo_9.write(0);
    }
    if (count ==1){
      delay(1000);
    }
    lcd.setCursor(0,0);
    lcd.print("Capacity : ");
    lcd.print(100 - percent);
    lcd.print(" %   ");
    lcd.setCursor(0,1);
    double a=lenght/100*(100-percent);
   // drawing black rectangles on LCD
    if (a>=1) {
      for (int i=1;i<a;i++) {
        lcd.write(4);
        b=i;
      }
      a=a-b;
    }
    peace=a*5;
  // drawing charater's colums
    switch (peace) {
    case 0:
      break;
    case 1:
      lcd.print(char(0));
      break;
    case 2:
      lcd.write(1);
      break;
    case 3:
      lcd.write(2);
      break;
    case 4:
      lcd.write(3);
      break;
    }
  //clearing line
    for (int i =0;i<(lenght-b);i++) {
      lcd.print(" ");
    }
    ;
  }
  if (buttonstate == LOW){
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("POWER OFF");
    lcd.setCursor(0, 1);
    lcd.print("VALVE & PUMP");
    delay(1000);
    digitalWrite(8, LOW);
    delay(1000);
    servo_9.write(0);
    delay(1500);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    delay(100);
    digitalWrite(10, HIGH);
    digitalWrite(13, LOW);
    count = 0;
  }
}
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C TV(0x27, 16, 2);

int piezoPin = 2;
int irPin = 9;

int Flag;
int notes[] = {6900, 4906, 6900, 4906, 6900};

void setup() {
  // put your zssetup code here, to run once:
  Serial.begin(9600);
  pinMode(piezoPin, OUTPUT);
  pinMode(irPin, INPUT);

  TV.init();
  TV.backlight();
  TV.setCursor(0, 0);
  TV.print("Looking TV...");
}

void loop() {
  // put your main code here, to run repeatedly:
  int IRVal = digitalRead(irPin);
  Serial.println(IRVal);

  if(IRVal == 0){
    if(Flag == 0){
      for (int i = 0; i < 5; i++){
        tone(piezoPin, notes[i], 150);
        delay(150);
      }
      Flag = 1;
     }
  TV.noBacklight();
  }
   else
   {
    TV.backlight();
    Flag = 0;
    }
   delay(100);
  }

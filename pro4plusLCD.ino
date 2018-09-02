#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 4);

int piezoPin = 2;
int airCon = 9;
int notes[] = {4186, 4698, 5274, 5587, 6271};

int C = 1047; //도 
int D = 1175; //레
int E = 1319; //미
int F = 1397; //파
int G = 1568; //솔
int A = 1760; //라
int B = 1976; //시
int BB = 2000; //도

int notes2[20] = { F, G, A, F, BB, A, G, BB, G, F, D, A, F, E, F, E, D, E, F, G
  };

boolean flag = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  
  Serial.begin(9600);
  
  dht.begin();
  pinMode(piezoPin, OUTPUT);
  pinMode(airCon, OUTPUT);
  lcd.init();
  lcd.backlight();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

}

void loop() {
  // put your main code here, to run repeatedly:

  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if(isnan(humidity)||isnan(temperature)){
   Serial.println("Failed to read from DHT sensor!");
   return; 
   }

  float discomfortIndex = (1.8 * temperature) - (0.55 * (1-humidity/100.0) * (1.8 * temperature - 26))+32;
  Serial.println(discomfortIndex);

  lcd.print("<dicomfortIndex> :");
  lcd.print(discomfortIndex);
  lcd.print("<Humi>: ");
  lcd.print(humidity);
  lcd.print("<Temp>: ");
  lcd.print(temperature);


  int cdsVal = analogRead(A0);

  
   if (discomfortIndex>70) {
    digitalWrite(airCon, HIGH);

    if (flag == 0) {
      for(int i = 0; i<5; i++){
          tone(piezoPin, notes[i], 300);
          delay(150);
      }
      flag = 1;
      for(int i = 0; i<2; i++){
      tone(piezoPin, notes2[i], 200);
      delay(200);
      }
      delay(500);
      for(int i = 2; i<7; i++){
      tone(piezoPin, notes2[i], 200);
      delay(200);
      }
      delay(500);
      for(int i = 7; i<10; i++){
      tone(piezoPin, notes2[i], 200);
      delay(200);
      }
      delay(500);
      for(int i = 7; i<20; i++){
      tone(piezoPin, notes2[i], 200);
      delay(300);
      }
    }
  }
  else
  {
   digitalWrite(airCon, LOW);
   flag = 0; 
    }
   delay(1500);
}

#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT11

int piezoPin = 2;
int airCon = 9;
int notes[] = {4186, 4698, 5274, 5587, 6271};

boolean flag = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  dht.begin();
  pinMode(piezoPin, OUTPUT);
  pinMode(airCon, OUTPUT);
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

  if (discomfortIndex>70) {
    digitalWrite(airCon, HIGH);

    if (flag == 0) {
      for(int i = 0; i<5; i++){
          tone(piezoPin, notes[i], 300);
          delay(150);
      }
      flag = 1;
    }
  }
  else
  {
   digitalWrite(airCon, LOW);
   flag = 0; 
    }
   delay(1500);
}

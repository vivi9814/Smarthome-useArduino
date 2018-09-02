int C = 1047;
int D = 1175;
int E = 1319;
int F = 1397;
int G = 1568;
int A = 1760;
int B = 1976;

int piezoPin = 2;

int cdsPin = A0;

int notes[25] = {G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C};

int tempo = 200;

void setup() {
   Serial.begin(9600);
   pinMode(piezoPin, OUTPUT);
  }

void loop() {
  // put your main code here, to run repeatedly:
  int cdsValue = analogRead(cdsPin);
  Serial.println(cdsValue);

  if(cdsValue>700){
    for(int i = 0; i< 12; i++){
      tone(piezoPin, notes[i], tempo);
      delay(300);
      }
      delay(100);

      for(int i = 12; i<25; i++){
        tone(piezoPin, notes[i],tempo);
        delay(300);
        }
    }
}

#include <dht.h>


#define LED1 7  //red
#define LED2 8  //green

const int GSR=A3;
int sensorValue;

#define dht_apin A0 

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int PulseSensorPurplePin = 1;       
int LED13 = 13;

boolean countStatus;
int beat, bpm;
unsigned long millisBefore;

dht DHT;
const int buzzer = 9;
int Signal;                

void setup(){
 
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  delay(500);
  delay(1000);
  delay(1000);
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT);
  pinMode(LED13,OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.println("Hum: ");
  lcd.setCursor(9,0);
    lcd.println("BPM: ");
  lcd.setCursor(0,1);
  lcd.println("Temp : ");
}
 
void loop(){ 
 
    DHT.read11(dht_apin);

      lcd.setCursor(5,0);
      lcd.print(String(int(DHT.humidity))+"% ");
      lcd.setCursor(7,1);
      lcd.println(int(DHT.temperature));
      lcd.setCursor(9,1);
      lcd.print(F("\xDF"" C"));
      digitalWrite(LED2,HIGH);
      
    if(DHT.humidity >= 65 && DHT.temperature > 36){
          
          digitalWrite(LED1,HIGH);
          digitalWrite(LED2,LOW);
          tone(buzzer, 1000);
          delay(500);       
          noTone(buzzer);
      }
      else
      {
          digitalWrite(LED2,HIGH);
          digitalWrite(LED1,LOW);
      }

  
int sensorValue = analogRead(A1);
  if (countStatus == 0)
  {
    if (sensorValue > 600)
    {
      countStatus = 1;
      beat++;
      
    }
  }
  else
  {
    if (sensorValue < 500)
    {
      countStatus = 0;
    }
  }
  if (millis() - millisBefore > 5000)
  {
    bpm = beat * 12;
    beat = 0;
    Serial.print(bpm);
    Serial.print(" ");
    lcd.setCursor(14,0);
    lcd.print(bpm);
    if(bpm > 100){
      digitalWrite(LED13,HIGH);
      tone(buzzer, 1000);
      delay(500);       
      noTone(buzzer);
      }
      else
      {
        digitalWrite(LED13,LOW);
       }
    millisBefore = millis();
  }

  float conductivevoltage;
  sensorValue=analogRead(GSR);
  conductivevoltage = sensorValue*(5.0/1023.0);
  Serial.println(sensorValue);
  delay(100);

  delay(1);  
 
}

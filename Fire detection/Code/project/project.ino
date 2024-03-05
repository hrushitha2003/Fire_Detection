#include <stdio.h>

#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


const char* ssid = "iotserver";
const char* password = "iotserver123";

WiFiClient  client;

unsigned long myChannelNumber = 2396109;
const char * myWriteAPIKey = "9LCLAMKNNWN8D98C";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;



int fan    = 15;
int fire   = 14;
int buzzer = 12;

void beep()
{
  digitalWrite(buzzer, HIGH);delay(2000);digitalWrite(buzzer, LOW);delay(500);
}
void setup() 
{
  Serial.begin(9600);

  pinMode(fan, OUTPUT);
  pinMode(fire, INPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(fan, LOW);
  digitalWrite(buzzer, LOW);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
    delay(5000);    
  ThingSpeak.begin(client);  // Initialize ThingSpeak
    delay(2000);
    
  lcd.init();
  lcd.backlight();
  delay(2000);

  lcd.clear();
  lcd.print("Fire:");  //5,0
 // serialEvent();
}
int sts1=0,sts2=0;
int cntlmk=0;
void loop() 
{
 
 if(digitalRead(fire) == LOW)
   {
    lcd.setCursor(5,0);lcd.print("ON  ");  

    digitalWrite(fan, HIGH);delay(1000);
    beep();

    sts1++;sts2=0;
    if(sts1 >= 2){sts1=2;}
    if(sts1 == 1)
      {
       ThingSpeak.setField(1, 100);
       ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      }
    }
   
 if(digitalRead(fire) == HIGH)
   {
    lcd.setCursor(5,0);lcd.print("OFF ");  
    digitalWrite(fan, LOW);delay(1000);
    
    sts2++;sts1=0;
    if(sts2 >= 2){sts2=2;}
    if(sts2 == 1)
      {
       ThingSpeak.setField(1, 0);
       ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      }
   }

 delay(1000);  
}

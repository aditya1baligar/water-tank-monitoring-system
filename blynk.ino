

#define BLYNK_TEMPLATE_ID "TMPLMQeQl-_6"
#define BLYNK_DEVICE_NAME "Water tank"
#define BLYNK_AUTH_TOKEN "lqcuTTsWrjnYoCwbOxqW5bw266_bf0fe"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 

char ssid[] = "Baligar";  // type your wifi name
char pass[] = "Baligar@850";  // type your wifi password
#define trig D3   // Trig pin
#define echo D4   // Echo Pin 
#define relay D5


int tankdepth =15 ;   // Change 1 according to your tank depth



BlynkTimer timer;
int pinValue = 0;


char auth[] = BLYNK_AUTH_TOKEN;
void PGM()
{
  if (pinValue == 1) {
    digitalWrite(relay, LOW);
  } else if (pinValue == 0) {
    digitalWrite(relay, HIGH);
   
  }
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  long level= tankdepth-cm;
  if (level<0)
  level=0;
  level = map(level,0,tankdepth-3,0,100);
  Blynk.virtualWrite(V1, level);

}

 
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, PGM);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
   digitalWrite(relay, HIGH);
  
}
BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}

void loop()
{
 
  Blynk.run();
  timer.run();
  }

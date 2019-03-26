#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <FastLED.h>

CRGB leds[12]; //ledek száma

char auth[] = "2cf547cd08ad409f9fe13f53dcdbc6fa";
char ssid[] = "BTHub6-N6F5";
char pass[] = "49WxGxbtwaYd";
BlynkTimer timer;

int R=255;
int G=255;
int B=255;
int V=255;
int K;
byte f;
int r;
int g;
int b;
int v;
int M;
int I=1000;
int i;
unsigned long t;

BLYNK_WRITE(V1){r = param.asInt();}
BLYNK_WRITE(V2){g = param.asInt();}
BLYNK_WRITE(V3){b = param.asInt();}
BLYNK_WRITE(V4){v = param.asInt();V=map(v,0,100,0,255);}
BLYNK_WRITE(V5){K = param.asInt();}
BLYNK_WRITE(V6){M = param.asInt();}
BLYNK_WRITE(V7){I = param.asInt();I=I*10;}

void myTimerEvent()
{
Blynk.virtualWrite(V0,millis()/1000);
Blynk.virtualWrite(V14,V);
Blynk.virtualWrite(V15,K); 
}
 
 

 
void setup(){
delay(2000); //valami miatt kell a ledhez 
Blynk.begin(auth, ssid, pass);
timer.setInterval(1000L, myTimerEvent);
FastLED.addLeds<WS2812,2, RGB>(leds,12); //led setup
 
Blynk.virtualWrite(V7,R);
Blynk.virtualWrite(V7,G);
Blynk.virtualWrite(V7,B);
Blynk.virtualWrite(V6,1); // üzemmod kapcsolo OFF ra kapcsol 
  
}
 
void loop()
{
  
Blynk.run();
timer.run();
switch(M)
{
case 1:ki();break;
case 2:be();break;
case 3:rnd();break;
case 4:m1();break;
case 5:m2();break;
default:ki();break;
}
}

void ki()
{
for(f= 0;f < 12;f++)
{leds[f]=CRGB::Black;
FastLED.show();}
}

void be()
{
G=map(r,0,255,0,V);
R=map(g,0,255,0,V);
B=map(b,0,255,0,V);
for(f= 0;f < 12;f++){
leds[f].setRGB(R,G,B);
FastLED.show();}
}


void rnd()
{
if(i>=I)
{
i=0; //nullázzuk a sürüség számlálot
G=random(V);
R=random(V);
B=random(V);
for(f= 0;f < 12;f++){
leds[f].setRGB(R,G,B);
FastLED.show();}  
}
i++;
}

void m1()
{
if(i>=I)
{
i=0; //nullázzuk a sürüség számlálot
for(f= 0;f < 12;f++){
leds[f].setRGB(random(V),random(V),random(V));
FastLED.show();}  
}
i++;
}

void m2()
{  
if(i>=I)
{
i=0;

for(f= 0;f < 12;f++){leds[f]=CRGB::Black;FastLED.show();} //ledek ki kapcs
leds[random(12)].setRGB(random(V),random(V),random(V));FastLED.show();

}
i++; 
}

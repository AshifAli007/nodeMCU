/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "1A566t1MQuWtXxA51mEAmlKDtjDPUwcP";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "linkNew_5g";
char pass[] = "1997*Fihsa";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
int isHigh = 0;
int isLow = 0;
BlynkTimer timer; // Announcing the timer
BLYNK_WRITE(V1)
{   
  int value = param.asInt(); // Get value as integer
  int x = param[0].asInt();
  if(x==0){
    digitalWrite(D3, HIGH);
  }else if(x==1){
    digitalWrite(D3, LOW);
  }
}
void sensorDataSend()
{
  timeClient.update();
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();

  if((currentHour == 20) && currentMinute <= 2){ // turn on light
      digitalWrite(D3, LOW); // same here
      Blynk.virtualWrite(V1, 1);
  }
  if((currentHour == 5) && currentMinute >= 30 && currentMinute<=32){ //turn of light
      digitalWrite(D3, HIGH); // same here
      Blynk.virtualWrite(V1, 0);
  }
//  if(isLow){
//    digitalWrite(D3, HIGH);
//    Blynk.virtualWrite(V1, 0);
//  }else{
//    digitalWrite(D3, LOW);
//    Blynk.virtualWrite(V1, 1);
//  }
//  isLow = !isLow;
//  Serial.print(currentHour);
//  Serial.print(" ");
//  Serial.print(currentMinute);
//  Serial.print(" ");
//  Serial.print(currentSecond);
//  Serial.print(" ");
//  Serial.println();
}
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(19800);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D3, HIGH);

  timer.setInterval(30000L, sensorDataSend);
}

void loop()
{
//  if((currentHour == 18 || currentHour == 6) && currentMinute <=2){ // turn on watering
//      digitalWrite(D1, LOW); // here LOW means HIGH somehow they are reversed
//  }
//  if((currentHour == 18 || currentHour == 6) && currentMinute == 3){ // turn off watering
//      Serial.println("inside if water turn on");
//      digitalWrite(D1, HIGH); // same here
//  }

//  if((currentHour == 20) && currentMinute <= 2){ // turn on light
//      digitalWrite(D3, LOW); // same here
//  }
//  if((currentHour == 5) && currentMinute >= 30 && currentMinute<=32){ //turn of light
//      digitalWrite(D3, HIGH); // same here
//  }


  Blynk.run();
  timer.run(); 
}

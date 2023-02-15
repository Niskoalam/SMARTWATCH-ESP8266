#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "Niskoalam";
const char *password = "Samprolam123";

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP,"pool.ntp.org");



void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  timeClient.setTimeOffset(25200);
}

void loop() {
  timeClient.update();
  getTimeRTC();
  //Serial.println(timeClient.getFormattedTime());

  delay(1000);
}

void getTimeRTC()
{
  unsigned long epochTime = timeClient.getEpochTime();
  //timeClient.update();
  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  
  
  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
     
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond); 

  struct tm *ptm = gmtime((time_t *)&epochTime);

  String weekDay = weekDays[timeClient.getDay()-1];
  Serial.print("Week Day: ");
  Serial.println(weekDay);  

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  int currentYear = ptm->tm_year;
  String yeaR = String(currentYear);
  Serial.print("Year: ");
  Serial.println(yeaR);
}

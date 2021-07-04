
// ----------------------------------
// QCLOCKTWO by Ph. Jounin
//
// ESP8266 version
// - setup: once started, the program tries to connect to a previously savec AP
//          if it fails, it set the ESP into Access Point mode
//          using a phone or a PC, connect to the AP qclocktwo and connect to http://192.168.4.1
//          to enter wifi credentials  
// - qlocktwo will now connects to the Wifi network, get its time and use the timezone set in wifi.cpp
// ----------------------------------


#include <ESP8266WiFi.h>  // wifi interface

#include "time2words.h"     // translate time hour/minute into "words" (pos + len)
#include "leds.h"           // display "words" on the led strip

// wiring 
#define WS2812_PIN        D2   // pin for time display (seems to be the only working pin (4)
#define HEARTBEAT_PIN     D5   // led hearbeat 
#define ON_DEMAND_VCC_PIN D0   // provide power for brightness measurements
#define PHOTORES_PIN      A0   // analogic pin to mesure brightness


void initPhotoRes (int VccPin, int SensorPin);
int detectPhotoRes (int VccPin, int SensorPin);
void init_Wifi();


// --------------------------------------------
// Setup : 
//    - init hertbeat pin for output
//    - init NeoPixel library
//    - set photoresistor pins
// --------------------------------------------


void setup()
{
  Serial.begin(115200);  //Starts serial connection
  pinMode (HEARTBEAT_PIN, OUTPUT);
  init_Wifi ();
  initLeds (WS2812_PIN);
  initPhotoRes (ON_DEMAND_VCC_PIN, PHOTORES_PIN);
  Serial.println ("setup 0 done");
} // setup 


// --------------------------------------------
// Main loop : 
// --------------------------------------------

// display time and brightness to serial console for debug !
void time_dbg(tm *ptm, int brightness)
{
static char buf[100];
  sprintf (buf,"year: %4d \tmonth: %02d\tday: %02d\thour: %02d\tmin: %02d\tsec: %02d\twday: %d",
            ptm->tm_year + 1900,  // years since 1900
            ptm->tm_mon + 1,      // January = 0 (!)
            ptm->tm_mday,         // day of month
            ptm->tm_hour,         // hours since midnight  0-23
            ptm->tm_min,          // minutes after the hour  0-59
            ptm->tm_sec,          // seconds after the minute  0-61*
            ptm->tm_wday,         // days since Sunday 0-6
            ptm->tm_isdst == 1 ? "DST" : "standard" );      
  Serial.println(buf);
  sprintf (buf, "brighntess indice: %d\n", brightness);
  Serial.println(buf);
} // tim_dbg



// display time on the led strip
void showTime() {
time_t now;                         // this is the epoch
tm tm;                              // the structure tm holds time information in a more convient way
static uint8_t last_minutes = -1;
struct s_Words wtime;
  time(&now);                       // read the current time (seconds after 1970)
  localtime_r(&now, &tm);           // convert it to day/hours/minutes/.. and in local time

  if (tm.tm_min!=last_minutes) // time has changed ?
  {
      // get smoothed brightness
      int brightness = detectPhotoRes (ON_DEMAND_VCC_PIN, PHOTORES_PIN);
      setBrightnessLeds (brightness);
       
        time_dbg (& tm, brightness);

      // get index of leds to be displayed
      time2words (& wtime, tm.tm_hour, tm.tm_min);
      // display them
      display_multiple_words (wtime.ledword, 6);
      // time has been updated !
      last_minutes = tm.tm_min;
  } // time to display ?
} // showTime
 

// here is the loop : 
//  - flip/flop a led 
//  - display the time
//  - wait for next second
void loop()
{
static int flap = LOW;
  // do an heartbeat control
   flap = (flap==LOW ? HIGH : LOW);
   digitalWrite (HEARTBEAT_PIN, flap);
   showTime();
   delay (1000);
}  // loop

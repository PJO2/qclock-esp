// ------------------------------
// Wifi inits
//    - Uses core ESP8266 to update time using NTP
//    - Set time zone
//    - starts in AP mode if wifi credentials are incorrect 
//      so you can connect to qclocktwo SSId and go to 192.168.4.1 to set new credentials
//  After that i hope that time is updated daily 
// ------------------------------

#include <ESP8266WiFi.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager


#define AP_SSID "qclocktwo"

/* Configuration of NTP */
#define MY_NTP_SERVER "europe.pool.ntp.org"           
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03" 

WiFiManager wm;    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around


// just wait for a connection in Station mode with a timeout
static bool wifi_connect(int timeout)
{
    while ( WiFi.status()!=WL_CONNECTED  && timeout-->=0 ) {
      delay(500);
      Serial.print(".");
   }
return timeout>=0 ;
}

// The main init
void init_Wifi() {
   bool res;

   configTime(MY_TZ, MY_NTP_SERVER); // --> Here is the IMPORTANT ONE LINER needed in your sketch!
   WiFi.mode(WIFI_STA);
    // Automatically connect using saved credentials,
   if (! wifi_connect (60) )
   {
        // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
        // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
        // then goes into a blocking loop awaiting configuration and will return success result
           // res = wm.autoConnect(); // auto generated AP name from chipid
        res = wm.autoConnect(AP_SSID); // anonymous ap
   }
   if (! wifi_connect (60) )  ESP.restart();
   Serial.println("");
   Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());

 } // init_Wifi

// Unuse but kept if you want to add a button to reset existing wifi credentials
void reset_Wifi()
{ 
    //reset settings - wipe credentials for testing
    wm.resetSettings();
}

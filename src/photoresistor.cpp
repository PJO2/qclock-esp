// ----------------------------------------
// measure the photo resistor voltage 
// Wiring is : Arduino PhotoVcc Pin -- photoresistor --- 1kOhm resistor -- GND
//                                                    | 
//                                          Arduino PhotoSensor Pin
//
// ----------------------------------------
#include <arduino.h>  // get digitalwrite/delay definitions

// brightness tuning
#define NB_VALS               6    // how many values are stored
#define BRIGHTNESS_MULTIPLIER 7    // may be increased to increase brightness
#define BRIGHTNESS_MINI       4    // may be increased to increase brightness

static int lightCal[NB_VALS];       // a circular buffer to save previous measures
static int read_idx=0;              // current position in the circular buffer
static int sum;                     // the sum of the circular buffer

// ------------------------------------------------------------------------------
// do a brightness measure :
//   - bring power pin up
//   - wait a few ms
//   - measure the voltage between the 1kOhm resistor and the 5628 photoresistor
//   - keep NB_VLAS measures to smoother the changes 
//   - do some math to render a measure which can be sent to the led strip  
// ------------------------------------------------------------------------------
int detectPhotoRes (int VccPin, int SensorPin)
{

  digitalWrite (VccPin, HIGH);       // Activate current just for a while
  delay (50);                       // wait for stabilisation (30ms according to datasheet)
  sum -= lightCal[read_idx];
  lightCal[read_idx] = analogRead(SensorPin); // measure
  sum += lightCal[read_idx];    // replace old value
  
  digitalWrite (VccPin, LOW);        // Do not waste power 
  
  read_idx++;
  read_idx %= NB_VALS;

  int bright =  BRIGHTNESS_MINI + sqrt ( sum / NB_VALS ) * BRIGHTNESS_MULTIPLIER;
  return bright > 255 ? 255 : bright ;
} // detectPhotoRes

// ------------------------------------------------------------------------------
// init : 
//     - set up ESP8266 pins
//     - fill up the measurement array
// ------------------------------------------------------------------------------
void initPhotoRes (int VccPin, int SensorPin)
{
  pinMode(VccPin,   OUTPUT);
  pinMode(SensorPin, INPUT);   

  // fill buffer
  for (int ark=0 ; ark<NB_VALS ; ark ++)
     detectPhotoRes (VccPin, SensorPin);
} // initPhotoRes

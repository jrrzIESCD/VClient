#include <ESP8266WiFi.h>
#include <E131.h>
#include <FastLED.h>

#define NUM_PIXELS 150  /* Number of pixels */
#define UNIVERSE 1      /* Universe to listen for */
#define CHANNEL_START 1 /* Channel to start listening at */
#define DATA_PIN 6      /* Pixel output - GPIO0 */

CRGB pixels[NUM_PIXELS];
E131 e131;

const char ssid[] = "Totalplay-289F";         /* Replace with your SSID */
const char passphrase[] = "289F3326cyutW26a";   /* Replace with your WPA2 passphrase */
int ini=0;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(pixels, NUM_PIXELS);
  /* Choose one to begin listening for E1.31 data */
  while (e131.begin(ssid, passphrase) != WL_CONNECTED);  
  /* via Unicast on the default port */
  for (int j=0; j<3; j++)
  {
    for (int i=0; i< NUM_PIXELS; i++)
    {
      pixels[i] = CRGB(255,255,255);
    }
    FastLED.show();
    delay(100);

    for (int i=0; i< NUM_PIXELS; i++)
    {
      pixels[i] = CRGB(0,0,0);
    }    
    FastLED.show();
    delay(100);
  }


  //e131.beginMulticast(ssid, passphrase, UNIVERSE);  /* via Multicast for Universe 1 */ 
}

void loop() {
  /* Parse a packet and update pixels */
  if(e131.parsePacket()) {
    if (e131.universe == UNIVERSE) {
      for (int i = 0; i < NUM_PIXELS; i++) {
          int j = i * 3 + (CHANNEL_START - 1);
          pixels[i] = CRGB(e131.data[j], e131.data[j+1], e131.data[j+2]);
      }
      FastLED.show();
    }
  }
//  test();
}

void test() {
  for(int i = ini; i < NUM_PIXELS; i++)
  {
    pixels[i] = CRGB(random(255), random(255), random(255));
    pixels[i-6] = CRGB(0, 0, 0);
    delay(100);
    FastLED.show();
  }

  for(int i = 143; i > 0; i--)
  {
    pixels[i] = CRGB(random(255), random(255), random(255));
    pixels[i+6] = CRGB(0, 0, 0);
    delay(100);
    FastLED.show();
  }
  ini = 6;
}

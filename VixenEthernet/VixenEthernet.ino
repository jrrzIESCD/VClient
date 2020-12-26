#include <SPI.h>
#include <Ethernet.h>
#include <E131.h>
#include <FastLED.h>

#define NUM_PIXELS 170
#define DATA_PIN 3

byte mac[] = { 0xDE, 0xAD, 0xBE, 0x2F, 0x1E, 0xE3 };

E131 e131;

void setup() {
    Serial.begin(115200);
    delay(10);

    /* Configure via DHCP and listen Unicast on the default port */
    e131.begin(mac);

    FastLED.addLeds<WS2811, DATA_PIN>((CRGB*)e131.data, NUM_PIXELS);
}

void loop() {
    /* Parse a packet and update pixels */
    if(e131.parsePacket())
        FastLED.show();
}

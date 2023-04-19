#include <Arduino.h>
#include <SoftwareSerial.h>
#include "arducrsf_rh.h"

#define RX_PIN 4
#define TX_PIN 5

SoftwareSerial Serial_my(RX_PIN, TX_PIN, true);
CRSF_RH elrs;
crsf_rc_channels channels;

void setup()
{
    // USB
    Serial.begin(115200);
    // ELRS
    Serial_my.begin(115200);
    while (!Serial_my)
    {
        Serial.println("EP2 waiting");
        delay(500);
    }

    elrs.set_port(&Serial_my);
    for (uint8_t i = 0; i < 16; i++)
    {
        channels.ch[i] = 173;
    }
}

void loop()
{
    if (channels.ch[0] > 1811)
    {
        for (uint8_t i = 0; i < 16; i++)
        {
            if (i == 5)
            {
                continue;
            }
            channels.ch[i] = 173;
        }
    }
    elrs.send_rc_channels(channels);
    delay(2);
    for (uint8_t i = 0; i < 16; i++)
    {
        if (i == 5)
        {
            continue;
        }
        channels.ch[i] = channels.ch[i] + 1;
    }
}
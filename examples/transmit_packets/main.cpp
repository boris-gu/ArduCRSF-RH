#include <Arduino.h>
#include "arducrsf_rh.h"

// =============================================================
// SoftSerial
// When using softserial, data transmission errors are possible
// and the maximum baud rate is limited to 115200
// =============================================================
/*
#include <SoftwareSerial.h>

#define RX_PIN 4
#define TX_PIN 5

uint16_t step;
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
    step = 1;
    for (uint8_t i = 0; i < 16; i++)
    {
        channels.ch[i] = 173;
    }
}
*/
//=====
// END
//=====

//========================
// 400k with TBS inverter
//========================
uint16_t step;
CRSF_RH elrs;
crsf_rc_channels channels;

void setup()
{
    // USB
    Serial.begin(460800);
    // ELRS
    Serial2.begin(400000);
    while (!Serial2)
    {
        delay(5);
    }

    elrs.set_port(&Serial2);
    step = 1;
    for (uint8_t i = 0; i < 16; i++)
    {
        channels.ch[i] = 173;
    }
}
//=====
// END
//=====

void loop()
{
    if (channels.ch[0] < 173 || channels.ch[0] > 1811)
    {
        step *= -1;
    }
    elrs.send_rc_channels(channels);
    delay(2);
    for (uint8_t i = 0; i < 16; i++)
    {
        channels.ch[i] = channels.ch[i] + step;
    }
}
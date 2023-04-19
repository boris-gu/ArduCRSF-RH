#pragma once
#include <Arduino.h>

// DEST
#define CRSF_ADDRESS_CRSF_TRANSMITTER 0xEE
#define CRSF_ADDRESS_RADIO_TRANSMITTER 0xEA
#define CRSF_ADDRESS_FLIGHT_CONTROLLER 0xC8
#define CRSF_ADDRESS_CRSF_RECEIVER 0xEC

// LEN
#define CRSF_LEN_MAX 62

// TYPE
#define CRSF_FRAMETYPE_RC_CHANNELS 0x16
#define CRSF_FRAMETYPE_DEVICE_PING 0x28
#define CRSF_FRAMETYPE_DEVICE_INFO 0x29
#define CRSF_FRAMETYPE_PARAMETER_SETTINGS_ENTRY 0x2B
#define CRSF_FRAMETYPE_PARAMETER_READ 0x2C
#define CRSF_FRAMETYPE_PARAMETER_WRITE 0x2D
#define CRSF_FRAMETYPE_COMMAND 0x32

// CRC
// #define POLY 0xD5

struct crsf_default
{
    uint8_t packet[CRSF_LEN_MAX];
    uint8_t *dest = &packet[0];
    uint8_t *len = &packet[1];
    uint8_t *type = &packet[2];
    uint8_t *payload = &packet[3];
    uint8_t *crc8;
};

struct crsf_rc_channels
{
    uint8_t dest;
    uint8_t len;
    uint8_t type;
    uint16_t ch[16];
    uint8_t crc8;
};

// [dest] [len] [type] [payload] [crc8]
class CRSF_RH
{
private:
    Stream *port;
    crsf_default tx;

    uint8_t crc8_calc(crsf_default *pkt);

public:
    CRSF_RH();
    CRSF_RH(Stream *port);
    bool set_port(Stream *port);
    bool send_model_id(uint8_t id);
    bool send_rc_channels(crsf_rc_channels channels);

};
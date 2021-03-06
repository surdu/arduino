//enhanced version of:
//credits: https://github.com/arildlangseid/vw_t4_tcu_temp_to_fis

#ifndef VW2002FISWriter_h
#define VW2002FISWriter_h

#include <inttypes.h>
#include <Arduino.h>

// based on FIS_emulator

#define FIS_WRITE_PULSEW 4
#define FIS_WRITE_START 15 //something like address, first byte is always 15

#define PORT_3LB PORTB
#define DATA  PB3 //MOSI (Arduino Uno 11)
#define CLK   PB5 //SCK (Arduino 13)


// Positions in Message-Array
#define FIS_MSG_COMMAND 0
#define FIS_MSG_LENGTH 1

static uint8_t off[] = {0x81, 18, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 98};
static uint8_t blank[] = {0x81, 18, 240, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 98};

class VW2002FISWriter
{
  public:
    VW2002FISWriter(uint8_t clkPin, uint8_t dataPin, uint8_t enaPin);
    ~VW2002FISWriter();
    void begin();

// void sendMsg(String line1, String line2, bool center=true);
    void sendMsg(char msg[]);
    void sendMsgFS(uint8_t X,uint8_t Y,uint8_t font,uint8_t size,char msg[]);
    void initScreen(uint8_t mode,uint8_t X,uint8_t Y,uint8_t X1,uint8_t Y1);
    void sendRawMsg(char in_msg[]);
void sendRawData(uint8_t data[]);
    void sendKeepAliveMsg();
    void displayOff();
    void displayBlank();
    void GraphicFromArray(uint8_t x,uint8_t y, uint8_t sizex,uint8_t sizey,uint8_t data[],uint8_t mode);
    void printFreeMem();
    void GraphicOut(uint8_t x,uint8_t y, uint16_t size, uint8_t data[],uint8_t mode,uint8_t offset);
    private:

    uint8_t _FIS_WRITE_CLK;
    uint8_t _FIS_WRITE_DATA;
    uint8_t _FIS_WRITE_ENA;

    void FIS_WRITE_send_3LB_msg(char in_msg[]);
    void FIS_WRITE_send_3LB_singleByteCommand(uint8_t txByte);
    void sendEnablePulse();
    void FIS_WRITE_3LB_sendByte(uint8_t in_byte);
    void FIS_WRITE_startENA();
    void FIS_WRITE_stopENA();
    void setClockHigh();
    void setClockLow();
    void setDataHigh();
    void setDataLow();
    void waitEnaHigh();
    uint8_t checksum( volatile uint8_t in_msg[]);

};


#endif

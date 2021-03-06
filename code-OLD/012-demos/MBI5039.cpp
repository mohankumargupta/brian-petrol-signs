#include "MBI5039.h"

#if defined(ESP8266)
#define MAX_PWM_VALUE 1023
#else
#define MAX_PWM_VALUE 255
#endif

void fakeisr(MBI5039 *m)
{
  m->isr();
}

#if defined(ARDUINO_ARCH_RP2040)
void MBI5039::isr() 
#elif defined(ESP8266)
void IRAM_ATTR MBI5039::isr() 
#endif
{
  fallingClockEdge = true;
  clockCount++;
}

void MBI5039::setBrightness(float b)
{
  brightness = (int) ((1.0 - b) * MAX_PWM_VALUE);
}

void MBI5039::disable()
{
  digitalWrite(noe_pin, HIGH);
}

void MBI5039::enable()
{
  analogWrite(noe_pin, brightness);
}

void MBI5039::latch()
{
  delayMicroseconds(250);
  digitalWrite(latch_pin, HIGH);
  delayMicroseconds(250);
  digitalWrite(latch_pin, LOW);
  delayMicroseconds(250);
}

void MBI5039::sendDataMSB(uint8_t *data1, uint8_t *data2, uint8_t *data3, uint8_t *data4)
{
    clockCount = 0;
    uint16_t mask = 0x80;

    sendOneBit(data1, data2, data3, data4, mask);
    #if defined(ARDUINO_ARCH_RP2040)
    attachInterrupt(clock_pin, fakeisr, FALLING, this);  
    #elif defined(ESP8266)
    attachInterrupt(clock_pin, std::bind(&MBI5039::isr, this), FALLING); 
    #endif
    analogWrite(clock_pin, 1023/2);

    while(true) 
    {
      if (fallingClockEdge) 
      {
        fallingClockEdge = false;

        if (clockCount == 8) 
        {
          clockCount = 0;
          detachInterrupt(clock_pin);
          digitalWrite(clock_pin, LOW);

          digitalWrite(data1_pin, LOW);
          digitalWrite(data2_pin, LOW);
          digitalWrite(data3_pin, LOW);
          digitalWrite(data4_pin, LOW);
          break;
        }

        else 
        {
          delayMicroseconds(200);
          mask = mask >> 1;
          sendOneBit(data1, data2, data3, data4, mask);
        }
      }
    }    

    
}

void MBI5039::sendDataLSB(uint8_t *data1, uint8_t *data2, uint8_t *data3, uint8_t *data4)
{
    clockCount = 0;
    uint16_t mask = 1;

    sendOneBit(data1, data2, data3, data4, mask);
    #if defined(ARDUINO_ARCH_RP2040)
    attachInterrupt(clock_pin, fakeisr, FALLING, this);  
    #elif defined(ESP8266)
    attachInterrupt(clock_pin, std::bind(&MBI5039::isr, this), FALLING); 
    #endif
    analogWrite(clock_pin, 1023/2);

    while(true) 
    {
      if (fallingClockEdge) 
      {
        fallingClockEdge = false;

        if (clockCount == 8) 
        {
          clockCount = 0;
          detachInterrupt(clock_pin);
          digitalWrite(clock_pin, LOW);

          digitalWrite(data1_pin, LOW);
          digitalWrite(data2_pin, LOW);
          digitalWrite(data3_pin, LOW);
          digitalWrite(data4_pin, LOW);
          break;
        }

        else 
        {
          delayMicroseconds(200);
          mask = mask << 1;
          sendOneBit(data1, data2, data3, data4, mask);
        }
      }
    }      
}

void MBI5039::sendData(uint16_t data1, uint16_t data2, uint16_t data3, uint16_t data4, bool bitOrder) 
{
  clockCount = 0;
  uint16_t mask;
  if (bitOrder) 
    mask = 1;
  else
    mask = 0x8000;

  sendOneBit(data1, data2, data3, data4, mask);
    #if defined(ARDUINO_ARCH_RP2040)
    attachInterrupt(clock_pin, fakeisr, FALLING, this);  
    #elif defined(ESP8266)
    attachInterrupt(clock_pin, std::bind(&MBI5039::isr, this), FALLING); 
    #endif
  analogWrite(clock_pin, 1023/2);


  while(true) 
  {
    if (fallingClockEdge) 
    {
      fallingClockEdge = false;

      if (clockCount == 16) 
      {
        clockCount = 0;
        detachInterrupt(clock_pin);
        digitalWrite(clock_pin, LOW);

        digitalWrite(data1_pin, LOW);
        digitalWrite(data2_pin, LOW);
        digitalWrite(data3_pin, LOW);
        digitalWrite(data4_pin, LOW);
        break;
      }

      else 
      {
        delayMicroseconds(200);
        if (bitOrder)
          mask = mask << 1;
        else
          mask = mask >> 1;
        sendOneBit(data1, data2, data3, data4, mask);

      }
    }
  }

}

void MBI5039::sendOneBit(uint8_t *data1, uint8_t *data2, uint8_t *data3, uint8_t *data4, uint16_t mask)
{
  digitalWrite(data1_pin, (*data1 & mask) ? HIGH:LOW);
  digitalWrite(data2_pin, (*data2 & mask) ? HIGH:LOW);
  digitalWrite(data3_pin, (*data3 & mask) ? HIGH:LOW);
  digitalWrite(data4_pin, (*data4 & mask) ? HIGH:LOW);  
}

void MBI5039::sendOneBit(uint16_t data1, uint16_t data2, uint16_t data3, uint16_t data4, uint16_t mask)
{
  digitalWrite(data1_pin, (data1 & mask) ? HIGH:LOW);
  digitalWrite(data2_pin, (data2 & mask) ? HIGH:LOW);
  digitalWrite(data3_pin, (data3 & mask) ? HIGH:LOW);
  digitalWrite(data4_pin, (data4 & mask) ? HIGH:LOW);
}

void MBI5039::myAnalogWrite(pin_size_t pin, int val) 
{
    mbed::PwmOut* pwm = new mbed::PwmOut(digitalPinToPinName(pin));
    //pwm->period_ms(2); //500Hz
    pwm->period_us(10); //100kHz
    float percent = val/255.0;
    pwm->write(percent);
}

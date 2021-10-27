#include "MBI5039.h"

#define PIN_DATA1 D2
#define PIN_DATA2 D1
#define PIN_DATA3 D6
#define PIN_DATA4 D8
#define PIN_CLK D7
#define PIN_LATCH D0
#define PIN_NOE D5

#define DATA_SEGMENTS_PER_PANEL 4

MBI5039 p3(PIN_CLK, PIN_LATCH, PIN_NOE, PIN_DATA1, PIN_DATA2, PIN_DATA3, PIN_DATA4);

//This lights up top left hand corner
void test1() 
{
  //p3.sendData(data4,data2, )
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000001, 0b0000000000000000, 0b0000000000000000, false);
}

//This lights up bottom right hand corner
void test2() 
{
  //p3.sendData(data4,data2, )
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000100000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
}

//This lights up Top right h0and corner
void test3() 
{
  //p3.sendData(data4,data2, )0
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000010000000, false);
}

//This lights up bottom left hand corner
void test4() 
{
  //p3.sendData(data4,data2,data1,data3)
  p3.sendData(0b1000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
  p3.sendData(0b0000000000000000, 0b0000000000000000, 0b0000000000000000, 0b0000000000000000, false);
}


void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_NOE, OUTPUT);
  pinMode(PIN_DATA1, OUTPUT);
  pinMode(PIN_DATA2, OUTPUT);
  pinMode(PIN_DATA3, OUTPUT);
  pinMode(PIN_DATA4, OUTPUT);
  
  digitalWrite(PIN_NOE, HIGH);
  digitalWrite(PIN_CLK, LOW);
  digitalWrite(PIN_LATCH, LOW);
  digitalWrite(PIN_DATA1, LOW);
  digitalWrite(PIN_DATA2, LOW);
  digitalWrite(PIN_DATA3, LOW);
  digitalWrite(PIN_DATA4, LOW);

  delay(1000);

  //0b0000000000000000
  //0b1111111111111111
  //0b1010101010101010
  //0b1110000000000101
  //0b0000000000000100
  //0b0000001100000000

  // Bad news: 1 is on ON, 0 is OFF

  //data4: u18-u21 
  //data3: u14-u17
  //data2: u10-u13
  //data1: u6-u9

  uint16_t data1 = 0b0111111111111111;
  uint16_t data2 = 0b1111111111111111;
  uint16_t data3 = 0b1111111111111111;
  uint16_t data4 = 0b1111111111111111;

  //test1();
  //test2();
  //test3();
  //test4();
  
  /*
  for (int i=0; i<DATA_SEGMENTS_PER_PANEL; i++)
  {
    p3.sendData(data1, data2, data3, data4, false);
    delayMicroseconds(250);
  }
*/
  /*
    p3.sendData(0b1111111111111111, 0b1111111111111111, 0b1111111111111111, 0b1111111100000000, false);
    p3.sendData(0b1111111111111111, 0b1111111111111111, 0b1111111111111111, 0b1111111111111111, false);
    p3.sendData(0b1111111111111111, 0b1111111111111111, 0b1111111111111111, 0b1111111111111111, false);
    p3.sendData(0b1111111111111111, 0b1111111111111111, 0b1111111111111111, 0b1111111111111111, false);   
   */

  digitalWrite(PIN_LATCH, HIGH);
  delayMicroseconds(250);
  digitalWrite(PIN_LATCH, LOW);
  delayMicroseconds(250);
  digitalWrite(PIN_NOE, LOW);
  analogWrite(PIN_NOE, 900);
  //delay(5000);
  //digitalWrite(PIN_NOE, HIGH);
}

int brightnessLevel = 1023;

void loop() {
  //analogWrite(PIN_NOE, brightnessLevel);
  //brightnessLevel -= 10;
  //delay(2000);
  //Serial.print("level:");
  //Serial.println(brightnessLevel);
  //digitalWrite(PIN_NOE, LOW);
  //delay(2000);
  //digitalWrite(PIN_NOE, HIGH);

  test1();
  digitalWrite(PIN_NOE, HIGH);
  digitalWrite(PIN_LATCH, HIGH);
  delayMicroseconds(250);
  digitalWrite(PIN_LATCH, LOW);
  delayMicroseconds(250);
  digitalWrite(PIN_NOE, LOW);
  analogWrite(PIN_NOE, 900);
  delay(1000);
  
  test2();
    digitalWrite(PIN_NOE, HIGH);
  digitalWrite(PIN_LATCH, HIGH);
  delayMicroseconds(250);
  digitalWrite(PIN_LATCH, LOW);
  delayMicroseconds(250);
  digitalWrite(PIN_NOE, LOW);
  analogWrite(PIN_NOE, 900);
  delay(1000);
  
  test3();
     digitalWrite(PIN_NOE, HIGH);
  digitalWrite(PIN_LATCH, HIGH);
  delayMicroseconds(250);
  digitalWrite(PIN_LATCH, LOW);
  delayMicroseconds(250);
  digitalWrite(PIN_NOE, LOW);
  analogWrite(PIN_NOE, 900);
  delay(1000); 
  
  test4();
    digitalWrite(PIN_NOE, HIGH);
  digitalWrite(PIN_LATCH, HIGH);
  delayMicroseconds(250);
  digitalWrite(PIN_LATCH, LOW);
  delayMicroseconds(250);
  digitalWrite(PIN_NOE, LOW);
  analogWrite(PIN_NOE, 900);
  delay(1000);
}

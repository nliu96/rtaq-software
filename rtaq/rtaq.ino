#include "Adafruit_ADS1015.h"
#include <SPI.h>
#include "DAC_MPS.h"
#include "Quantizer.h"
#include "Scale.h"

const int ANALOG = 0;
Adafruit_ADS1115 ads1115;
const int PIN_CSA = 9;
const int PIN_CSB = 10;
DAC_MPS dac1(0, PIN_CSA);
DAC_MPS dac2(1, PIN_CSA);
DAC_MPS dac3(0, PIN_CSB);
DAC_MPS dac4(1, PIN_CSB);
const int ledPin = LED_BUILTIN;
IntervalTimer timer;

unsigned int a[] = {
    0, 1200};
Quantizer quantizer(a, 2);
unsigned int scale[] = {};

void setup()
{
  SPI.begin();
  ads1115.begin();
  ads1115.setGain(GAIN_TWOTHIRDS);
  Serial.begin(38400);
  timer.begin(readAndOutput, 20000);
}

float val;
int i;

void readAndOutput() {
  unsigned int j;
  val = 0.2235 * ((float)ads1115.readADC_SingleEnded(0));
  i = (int)val;
  j = quantizer.quantize(i);
  j = j / 2;
  dac1.setOutput(j);
  dac2.setOutput(j);
  dac3.setOutput(j);
  dac4.setOutput(j);
}

int ledState = LOW;

void loop()
{
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
  delay(300);
}

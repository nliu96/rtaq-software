#include "Adafruit_ADS1015.h"
#include <SPI.h>
#include "DAC_MPS.h"
#include "Quantizer.h"
#include "Scale.h"
#include "WeirdQuantizer.h"

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


float a[] = { 0.0, 300, 500, 700, 1000, 1200 };
Scale scale(a, 6);
Quantizer quantizer(&scale);

void setup()
{
  SPI.begin();
  ads1115.begin();
  ads1115.setGain(GAIN_TWOTHIRDS);
  Serial.begin(38400);
  timer.begin(readAndOutput, 2000000);
}

float val;
int i;
int aInd = 0;
float expected[] = { 0.0, 300, 500, 700, 1000, 1200,
							1500, 1700, 1900, 2200, 2400,
							2700, 2900, 3100, 3400, 3600,
							3900, 4100, 4300, 4600, 4800,
							5100, 5300, 5500, 5800, 6000,
							6300, 6500, 6700, 7000, 7200 };

void readAndOutput() {

  float aWeird[] = { 200, 400, 500, 700,
			900, 1100, 1200 };
  Scale scaleWeird(aWeird, 7);
  WeirdQuantizer quantizahh = WeirdQuantizer(&scaleWeird, 6, 3);

  float j;
  val = 0.2235 * ((float)ads1115.readADC_SingleEnded(0));
  i = val;
  j = quantizer.quantize(expected[aInd % 31]);
  Serial.print(j);
  Serial.print(", expected:");
  Serial.println(expected[aInd % 31]);

  float inArr[] = { expected[aInd % 31], expected[aInd % 31], 
	  expected[aInd % 31], expected[aInd % 31] };
  float* arrOut = quantizahh.quantize(inArr);
  for (int i = 0; i < 4; i++) {
	  Serial.print(arrOut[i]);
	  Serial.print(", ");
  }
  Serial.print("input: ");
  Serial.println(expected[aInd % 31]);

  aInd++;
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

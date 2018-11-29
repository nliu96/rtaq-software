#include "Adafruit_ADS1015.h"
#include <SPI.h>
//#include <SdFat.h>
#include "DAC_MPS.h"
#include "Quantizer.h"
#include "Scale.h"
#include "WeirdQuantizer.h"
#include <Encoder.h>
//#include "WaveTable.h"
//#include <Wire.h>
//#include <string>

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
Encoder knob(32, 31);

//void readAndOutput();

/*float a[] = { 0.0, 300, 500, 700, 1000, 1200 };
Scale scale(a, 6);
Quantizer quantizer(&scale);*/

void setup()
{
  //Wire.setSDA(1);
  //Wire.setSCL(0);
  //Wire.begin();
  SPI.setSCK(27);
  SPI.begin();
  ads1115.begin();
  ads1115.setGain(GAIN_TWOTHIRDS);
  Serial.begin(38400);
  //Serial.println("initialized");
  //loadTable();
  //Serial.println("wavetable loaded");
  /*for (int i = 0; i < 127; i++) {
      for (int j = 0; j < 127; j++) {
        float tbval = getWaveTableValue(i, j);
        Serial.print(tbval);
        Serial.print(", "); 
      }
      Serial.println(" ");
  }*/
  timer.begin(readAndOutput, 200000);
}

float val;
//int i;
//int aInd = 0;
int ADC_;
int AMP_;
int DEST_;
int MU1_;
int TF1_;
int MU2_;
int TF2_;
int SPREAD_;
int SHIFT_;
int OFFSET_;
int DP_;
int MIX_;
int DENSITY_;
int JAZZ_;
int CHROM_;
long pos = -999;

/*float expected[] = { 0.0, 300, 500, 700, 1000, 1200,
							1500, 1700, 1900, 2200, 2400,
							2700, 2900, 3100, 3400, 3600,
							3900, 4100, 4300, 4600, 4800,
							5100, 5300, 5500, 5800, 6000,
							6300, 6500, 6700, 7000, 7200 };*/

void readAndOutput() {
  
  
  ADC_ = 1023 - analogRead(A9);
  AMP_ = analogRead(A8);
  DEST_ = analogRead(A7);
  MU1_ = 1023 - analogRead(A6);
  TF1_ = 1023 - analogRead(A3);
  MU2_ = 1023 - analogRead(A2);
  TF2_ = 1023 - analogRead(A1);
  SPREAD_ = analogRead(A0);
  SHIFT_ = analogRead(A22);
  OFFSET_ = 1023 - analogRead(A21);
  DP_ = analogRead(A20);
  MIX_ = 1023 - analogRead(A19);
  DENSITY_ = 1023 - analogRead(A18);
  JAZZ_ = analogRead(A17);
  CHROM_ = analogRead(A16);

  

  float aWeird[] = {200, 400, 600, 700, 900, 1100, 1200};
  int s = 7;
  
  Scale scaleWeird(aWeird, s);
  
  int scalenotes;
  int qnotes;
  int shift;
  scalenotes = (int)((((float)CHROM_)/1023.0)*s);
  qnotes = (int)((((float)DENSITY_)/1023.0)*scalenotes);
  shift = (int)(((float)SHIFT_)/1023.0);
  Serial.println(pos/4);
  WeirdQuantizer quantizahh = WeirdQuantizer(&scaleWeird, /*mainScaleNotes = */s, /*quantScaleNotes = */s, /*shift = */0);

  //float j;
  val = 0.2235 * ((float)ads1115.readADC_SingleEnded(0));
  //Serial.println(val);
  //i = val;
  //j = quantizer.quantize(expected[aInd % 31]);
  /*Serial.print(j);
  Serial.print(", expected:");
  Serial.println(expected[aInd % 31]);*/

  float inArr[] = {val, val, val, val};
  float* arrOut = quantizahh.quantize(inArr);
  for (int i = 0; i < 4; i++) {
	  //Serial.print(arrOut[i]);
	  //Serial.print(", ");
  }
  //Serial.print("input: ");
  //Serial.println(expected[aInd % 31]);

  //aInd++;
  //j = j / 2;
  dac1.setOutput(arrOut[0]/2);
  dac2.setOutput(arrOut[1]/2);
  dac3.setOutput(arrOut[2]/2);
  dac4.setOutput(arrOut[3]/2);
  delete[] arrOut;
}

int ledState = LOW;
void loop()
{
  long newpos;
  newpos = knob.read();
  pos = newpos;
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }

  digitalWrite(ledPin, ledState);
  delay(300);
}

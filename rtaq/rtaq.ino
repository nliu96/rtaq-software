#include "Adafruit_ADS1015.h"
#include <SPI.h>
//#include <SdFat.h>
#include "DAC_MPS.h"
#include "Quantizer.h"
#include "Scale.h"
#include "WeirdQuantizer.h"
#include <Encoder.h>
#include "WaveTable.h"
//#include <Wire.h>
//#include <string>

const int ANALOG = 0;
Adafruit_ADS1115 ads1115;
Waave wavetable = Waave();
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

  //wavetable parameter definition
  int idxtf1 = (int)((((float)TF1_)/1023.0)*127);
  int idxtf2 = (int)((((float)TF2_)/1023.0)*127);

  int delta13 = (int)((((float)MU1_)/1023.0)*127);
  int delta12 = (int)((((float)MU1_)/1023.0)*95);
  int delta11 = (int)((((float)MU1_)/1023.0)*63);
  int delta10 = (int)((((float)MU1_)/1023.0)*31);

  int delta23 = (int)((((float)MU2_)/1023.0)*127);
  int delta22 = (int)((((float)MU2_)/1023.0)*95);
  int delta21 = (int)((((float)MU2_)/1023.0)*63);
  int delta20 = (int)((((float)MU2_)/1023.0)*31);

  int idx_ch0_tf1 = (idxtf1 + delta10) % 127;
  int idx_ch1_tf1 = (idxtf1 + delta11) % 127; 
  int idx_ch2_tf1 = (idxtf1 + delta12) % 127;
  int idx_ch3_tf1 = (idxtf1 + delta13) % 127;

  int idx_ch0_tf2 = (idxtf2 + delta20) % 127;
  int idx_ch1_tf2 = (idxtf2 + delta21) % 127;
  int idx_ch2_tf2 = (idxtf2 + delta22) % 127;
  int idx_ch3_tf2 = (idxtf2 + delta23) % 127;
  
  //scale construction
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
  WeirdQuantizer quantizahh = WeirdQuantizer(&scaleWeird, /*mainScaleNotes = */scalenotes, /*quantScaleNotes = */qnotes, /*shift = */shift);

  val = 0.2235 * ((float)ads1115.readADC_SingleEnded(0));
  int val_127 = (int)((val/0.2235)/256);

  //wavetable mapping and lookup
  int idx10 = ((127*idx_ch0_tf1) + val_127) % 16384;
  int idx11 = ((127*idx_ch1_tf1) + val_127) % 16384;
  int idx12 = ((127*idx_ch2_tf1) + val_127) % 16384;
  int idx13 = ((127*idx_ch3_tf1) + val_127) % 16384;

  int idx20 = ((127*idx_ch0_tf2) + val_127) % 16384;
  int idx21 = ((127*idx_ch1_tf2) + val_127) % 16384;
  int idx22 = ((127*idx_ch2_tf2) + val_127) % 16384;
  int idx23 = ((127*idx_ch3_tf2) + val_127) % 16384;

  float val10 = 8192.0*wavetable.getTable()[idx10];
  float val11 = 8192.0*wavetable.getTable()[idx11];
  float val12 = 8192.0*wavetable.getTable()[idx12];
  float val13 = 8192.0*wavetable.getTable()[idx13];

  float val20 = 8192.0*wavetable.getTable()[idx20];
  float val21 = 8192.0*wavetable.getTable()[idx21];
  float val22 = 8192.0*wavetable.getTable()[idx22];
  float val23 = 8192.0*wavetable.getTable()[idx23];

  //wavetable mix
  float k = ((float)MIX_)/1023.0;

  float val0;
  float val1;
  float val2;
  float val3;
  
  int op = 0;
  if (op == 0){
    val0 = 0.5*(k*val10 + (1-k)*val20);
    val1 = 0.5*(k*val11 + (1-k)*val21);
    val2 = 0.5*(k*val12 + (1-k)*val22);
    val3 = 0.5*(k*val13 + (1-k)*val23);
  }

  Serial.print(idx10);
  Serial.print(", ");
  Serial.print(idx11);
  Serial.print(", ");
  Serial.print(idx12);
  Serial.print(", ");
  Serial.print(idx13);
  Serial.println(' ');
  
  float inArr[] = {val0, val1, val2, val3};
  float* arrOut = quantizahh.quantize(inArr);
  
  for (int i = 0; i < 4; i++) {
	  //Serial.print(arrOut[i]);
	  //Serial.print(", ");
  }

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

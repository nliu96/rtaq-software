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
void readAndOutput();
void scaleSelect();
void setup()
{
  Serial.begin(38400);
  while( !Serial );
  Serial.flush();
  Serial.println("initialized");
  //SPI.setSCK(27);
  SPI.begin();
  ads1115.begin();
  ads1115.setGain(GAIN_TWOTHIRDS);

  pinMode(30, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);

  timer.begin(readAndOutput, 200000);
  //attachInterrupt(digitalPinToInterrupt(29), readAndOutput, FALLING);
  //attachInterrupt(digitalPinToInterrupt(30), scaleSelect, FALLING);
}

float aTT[] = { 0.0, 300, 500, 700, 1000, 1200 };
Scale scaleTT(aTT, 6);
//WeirdQuantizer quantizahh = WeirdQuantizer();
WeirdQuantizer quantizahh = WeirdQuantizer(&scaleTT, 4, 2);

float val;
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
int ORDER_;
long pos = -999;
long sss = 5;

/*float expected[] = { 0.0, 300, 500, 700, 1000, 1200,
							1500, 1700, 1900, 2200, 2400,
							2700, 2900, 3100, 3400, 3600,
							3900, 4100, 4300, 4600, 4800,
							5100, 5300, 5500, 5800, 6000,
							6300, 6500, 6700, 7000, 7200 };*/
int ery = 0;
void readAndOutput() {
  //Serial.println(ery++);
  //ADC_ = 1023 - analogRead(A9);
  //AMP_ = analogRead(A8);
  //DEST_ = analogRead(A7);
  MU1_ = 1023 - analogRead(A6);
  TF1_ = 1023 - analogRead(A3);
  MU2_ = 1023 - analogRead(A2);
  TF2_ = 1023 - analogRead(A1);
  SPREAD_ = analogRead(A0);
  SHIFT_ = 1023 - analogRead(A22);
  //OFFSET_ = 1023 - analogRead(A21);
  DP_ = analogRead(A20);
  MIX_ = 1023 - analogRead(A19);
  DENSITY_ = 1023 - analogRead(A18);
  //JAZZ_ = analogRead(A17);
  CHROM_ = analogRead(A16);
  //ORDER_ = analogRead(A15); 

  //Serial.println(MU1_);
  //Serial.println(TF1_);
  //Serial.println(MU2_);
  //Serial.println(TF2_);
  //Serial.println(SPREAD_);
  //Serial.println(SHIFT_);
  //Serial.println(OFFSET_);
  //Serial.println(DP_);
  //Serial.println(MIX_);
  //Serial.println(DENSITY_);
  //Serial.println(JAZZ_);
  //Serial.println(CHROM_);
  //Serial.println(ORDER_);

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

 
  //float fake[] = {1200};
  //Scale scaleWeird(fake, 1);
  //quantizahh.set(&scaleWeird, 1, 1, 0);
  //scale lookup
  int n = 6;
  // TODO: change utils. instead of returning pointer to scale when index factor is bad, return a copy of it
  switch (sss % n){
  //switch(0) {
  case 0: {
	  float aWeird[] = { 1200 };
	  int s = 1;
	  Scale scaleWeird(aWeird, s);
	  int scalenotes = (int)((((float)CHROM_) / 1023.0)*s);
	  int qnotes = (int)((((float)DENSITY_) / 1023.0)*scalenotes);
	  int shift = (int)(((float)SHIFT_) / 1023.0);
	  scalenotes = s;
	  qnotes = s;
	  shift = 0;
      quantizahh.set(&scaleWeird, /*mainScaleNotes = */scalenotes, /*quantScaleNotes = */qnotes, /*shift = */shift);}
      break;
      
    case 1:{
      float aWeird[] = {300, 500, 700, 1000, 1200};
      int s = 5;
      Scale scaleWeird(aWeird, s);      
      int scalenotes = (int)((((float)CHROM_)/1023.0)*s);
      int qnotes = (int)((((float)DENSITY_)/1023.0)*scalenotes);
      int shift = (int)(((float)SHIFT_)/1023.0);
      scalenotes = s;
      qnotes = s;
      shift = 0;
      quantizahh.set(&scaleWeird, /*mainScaleNotes = */scalenotes, /*quantScaleNotes = */qnotes, /*shift = */shift);}
      break;
      
    case 2:{
      float aWeird[] = {200, 400, 700, 900, 1200};
      int s = 5;
      Scale scaleWeird(aWeird, s);      
      int scalenotes = (int)((((float)CHROM_)/1023.0)*s);
      int qnotes = (int)((((float)DENSITY_)/1023.0)*scalenotes);
      int shift = (int)(((float)SHIFT_)/1023.0);
      scalenotes = s;
      qnotes = s;
      shift = 0;
      quantizahh.set(&scaleWeird, /*mainScaleNotes = */scalenotes, /*quantScaleNotes = */qnotes, /*shift = */shift);}
      break;
      
    case 3:{
      float aWeird[] = {200, 300, 500, 700, 800, 1000, 1200};
      int s = 7;
      Scale scaleWeird(aWeird, s);      
      int scalenotes = (int)((((float)CHROM_)/1023.0)*s);
      int qnotes = (int)((((float)DENSITY_)/1023.0)*scalenotes);
      int shift = (int)(((float)SHIFT_)/1023.0);
      scalenotes = s;
      qnotes = s;
      shift = 0;
      quantizahh.set(&scaleWeird, /*mainScaleNotes = */scalenotes, /*quantScaleNotes = */qnotes, /*shift = */shift);}
      break;
      
    case 4:{
      float aWeird[] = {200, 400, 500, 700, 900, 1100, 1200};
      int s = 7;
      Scale scaleWeird(aWeird, s);      
      int scalenotes = (int)((((float)CHROM_)/1023.0)*s);
      int qnotes = (int)((((float)DENSITY_)/1023.0)*scalenotes);
      int shift = (int)(((float)SHIFT_)/1023.0);
      scalenotes = s;
      qnotes = s;
      shift = 0;
      quantizahh.set(&scaleWeird, /*mainScaleNotes = */scalenotes, /*quantScaleNotes = */qnotes, /*shift = */shift);}
      break;
      
    case 5:{
      //Serial.println("in case");
      float aWeird[] = {200, 400, 600, 700, 900, 1100, 1200};
      int s = 7;
      Scale scaleWeird(aWeird, s);
      
      int scalenotes = (int)((((float)CHROM_)/1023.0)*s);
      int qnotes = (int)((((float)DENSITY_)/1023.0)*scalenotes);
      int shift = (int)(((float)SHIFT_)/1023.0);
      scalenotes = s;
      qnotes = s;
      shift = 0;
      quantizahh.set(&scaleWeird, /*mainScaleNotes = */scalenotes, /*quantScaleNotes = */qnotes, /*shift = */shift);}
      break;

    default:{
      int s = 0;}
      break;
  }

  val = 0.2235 * ((float)ads1115.readADC_SingleEnded(0));
  int val_127 = (int)((val/0.2235)/256);

  idx_ch0_tf1 = 0;
  idx_ch1_tf1 = 0;
  idx_ch2_tf1 = 0;
  idx_ch3_tf1 = 0;
  idx_ch0_tf2 = 0;
  idx_ch1_tf2 = 0;
  idx_ch2_tf2 = 0;
  idx_ch3_tf2 = 0;
  
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

  int op = (int)((((float)DP_)/1023.0)*3);
  op = 0;
  if (op == 0){
    //arithmetic avg
    val0 = (k*val20 + (1-k)*val10);
    val1 = (k*val21 + (1-k)*val11);
    val2 = (k*val22 + (1-k)*val12);
    val3 = (k*val23 + (1-k)*val13);
  }
  else if (op == 1){
    //geometric avg
    val0 = 2*sqrt(k*val20 + (1-k)*val10);
    val1 = 2*sqrt(k*val21 + (1-k)*val11);
    val2 = 2*sqrt(k*val22 + (1-k)*val12);
    val3 = 2*sqrt(k*val23 + (1-k)*val13);
  }
    else if (op == 2){
    //min
    val0 = k*2*min(val10,val20);
    val1 = k*2*min(val11,val21);
    val2 = k*2*min(val12,val22);
    val3 = k*2*min(val13,val23);
  }
    else if (op == 3){
    //max
    val0 = k*2*max(val10,val20);
    val1 = k*2*max(val11,val21);
    val2 = k*2*max(val12,val22);
    val3 = k*2*max(val13,val23);
  }


  //chebyshev polynomials
  
  int order = (int)((((float)SPREAD_)/1023.0)*6);
  order = 1;
  
  float nval0 = val0/8096.0;
  float nval1 = val1/8096.0;
  float nval2 = val2/8096.0;
  float nval3 = val3/8096.0;
  
  if (order == 0) {
    val0 = 0;
    val1 = 1200;
    val2 = 2400;
    val3 = 3600;
  }
  else if (order == 1) {
    val0 = val0;
    val1 = val1;
    val2 = val2;
    val3 = val3;
  }
  else if (order == 2) {
    val0 = 8096.0*fabs(2*nval0*nval0 - 1);
    val1 = 8096.0*fabs(2*nval1*nval1 - 1);
    val2 = 8096.0*fabs(2*nval2*nval2 - 1);
    val3 = 8096.0*fabs(2*nval3*nval3 - 1);
  }
  else if (order == 3) {
    val0 = 8096.0*fabs(4*nval0*nval0*nval0 - 3*nval0);
    val1 = 8096.0*fabs(4*nval1*nval1*nval1 - 3*nval1);
    val2 = 8096.0*fabs(4*nval2*nval2*nval2 - 3*nval2);
    val3 = 8096.0*fabs(4*nval3*nval3*nval3 - 3*nval3);
  }
  else if (order == 4) {
    val0 = 8096.0*fabs(8*nval0*nval0*nval0*nval0 - 8*nval0*nval0 + 1);
    val1 = 8096.0*fabs(8*nval1*nval1*nval1*nval1 - 8*nval1*nval1 + 1);
    val2 = 8096.0*fabs(8*nval2*nval2*nval2*nval2 - 8*nval2*nval2 + 1);
    val3 = 8096.0*fabs(8*nval3*nval3*nval3*nval3 - 8*nval3*nval3 + 1);
  }
  else if (order == 5) {
    val0 = 8096.0*fabs(16*nval0*nval0*nval0*nval0*nval0 - 20*nval0*nval0*nval0 + 5*nval0);
    val1 = 8096.0*fabs(16*nval1*nval1*nval1*nval1*nval1 - 20*nval1*nval1*nval1 + 5*nval1);
    val2 = 8096.0*fabs(16*nval2*nval2*nval2*nval2*nval2 - 20*nval2*nval2*nval2 + 5*nval2);
    val3 = 8096.0*fabs(16*nval3*nval3*nval3*nval3*nval3 - 20*nval3*nval3*nval3 + 5*nval3);
  }
  else if (order == 6) {
    val0 = 8096.0*fabs(32*nval0*nval0*nval0*nval0*nval0*nval0 - 48*nval0*nval0*nval0*nval0 + 18*nval0*nval0 - 1);
    val1 = 8096.0*fabs(32*nval1*nval1*nval1*nval1*nval1*nval1 - 48*nval1*nval1*nval1*nval1 + 18*nval1*nval1 - 1);
    val2 = 8096.0*fabs(32*nval2*nval2*nval2*nval2*nval2*nval2 - 48*nval2*nval2*nval2*nval2 + 18*nval2*nval2 - 1);
    val3 = 8096.0*fabs(32*nval3*nval3*nval3*nval3*nval3*nval3 - 48*nval3*nval3*nval3*nval3 + 18*nval3*nval3 - 1);
  }


  //quantizahh.set(&scaleTT, /*mainScaleNotes = */4, /*quantScaleNotes = */2, /*shift = */0);
  float inArr[] = {val0, val1, val2, val3};
  float* arrOut = quantizahh.quantize(inArr);
  //float arrOut[] = {1, 2, 3, 4};
  //Serial.flush();
  for (int i = 0; i < 4; i++) {
	  Serial.print(arrOut[i]);
	  Serial.print(", ");
  }
  Serial.println("..");
  //Serial.println("hello");
  dac1.setOutput(arrOut[0]/2);
  dac2.setOutput(arrOut[1]/2);
  dac3.setOutput(arrOut[2]/2);
  dac4.setOutput(arrOut[3]/2);

  delete[] arrOut;
}

void scaleSelect() {
  sss = pos/4;
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
  //Serial.println(sss);
  //Serial.println(newpos/4);
  digitalWrite(ledPin, ledState);
  delay(300);
}

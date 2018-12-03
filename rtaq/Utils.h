#include "Scale.h"

#ifndef UTILS_H_
#define UTILS_H_

#pragma optimize("", off)
class Utils {
public:
	static Scale* generateSubScale(Scale* scale, int numNotes, int shift=0) {
		int originalScaleSize = scale->getScaleSize();
		float indexFactor = (float) originalScaleSize / numNotes;
		
		// Just return the original scale, # notes is wrong
		if (indexFactor < 1.0) {
			indexFactor = 1.0;
			numNotes = originalScaleSize;
		}
		
		float* tempCentsScale = new float[numNotes];
		float* originalCentsScale = scale->getCentsScale();

		// Place equal distance indices in new array
		for (int i = 0; i < numNotes; i++) {
			int scaledIndex = (int)(i*indexFactor);
			float thaThing = 
				originalCentsScale[shiftIndex(scaledIndex, shift, originalScaleSize)];
			tempCentsScale[i] = originalCentsScale[
					shiftIndex(scaledIndex, shift, originalScaleSize)];
		}
		Scale* outScale = new Scale(tempCentsScale, numNotes, false);
		delete[] tempCentsScale;
		return outScale;
	};
	static Scale* getKnobScales() {
		float aWeird[] = { 1200 };
		int s = 1;
		Scale scaleWeird(aWeird, s);
		float aWeird1[] = {200, 400, 700, 900, 1200}; //major pentatonic
    s = 5;
    Scale scaleWeird1(aWeird1, s);
    float aWeird2[] = {300, 500, 700, 1000, 1200}; //minor pentatonic
    s = 5;
    Scale scaleWeird2(aWeird2, s);
    float aWeird3[] = {200, 400, 500, 700, 900, 1100, 1200}; //ionian
    s = 7;
    Scale scaleWeird3(aWeird3, s);
    float aWeird4[] = {200, 300, 500, 700, 900, 1000, 1200}; //dorian
    s = 7;
    Scale scaleWeird4(aWeird4, s);
    float aWeird5[] = {100, 300, 500, 700, 800, 1000, 1200}; //phrygian
    s = 7;
    Scale scaleWeird5(aWeird5, s);
    float aWeird6[] = {200, 400, 600, 700, 900, 1100, 1200}; //lydian
    s = 7;
    Scale scaleWeird6(aWeird6, s);
    float aWeird7[] = {200, 400, 500, 700, 900, 1000, 1200}; //myxolydian
    s = 7;
    Scale scaleWeird7(aWeird7, s);
    float aWeird8[] = {200, 300, 500, 700, 800, 1000, 1200}; //aeolian
    s = 7;
    Scale scaleWeird8(aWeird8, s);
    float aWeird9[] = {100, 300, 500, 600, 800, 1000, 1200}; //locrian
    s = 7;
    Scale scaleWeird9(aWeird9, s);
    float aWeird10[] = {204, 408, 702, 906, 1200}; //major pentatonic pythagoran
    s = 5;
    Scale scaleWeird10(aWeird10, s);
    float aWeird11[] = {294, 498, 702, 996, 1200}; //minor pentatonic pythagoran
    s = 5;
    Scale scaleWeird11(aWeird11, s);
    float aWeird12[] = {184, 342, 534, 686, 870, 1074, 1200}; //indian a
    s = 7;
    Scale scaleWeird12(aWeird12, s);
    float aWeird13[] = {204, 386, 590, 702, 906, 1088, 1200}; //indian magrama
    s = 7;
    Scale scaleWeird13(aWeird13, s);
    float aWeird14[] = {200, 266, 316, 498, 702, 764, 814, 996, 1200}; //raga Darbari Kanada
    s = 9;
    Scale scaleWeird14(aWeird14, s);
    float aWeird15[] = {204, 386, 498, 702, 1088, 1200}; //indian raja
    s = 6;
    Scale scaleWeird15(aWeird15, s);
    float aWeird16[] = {424, 494, 918, 1130, 1200}; //Sorog madenda sejati, Sunda
    s = 5;
    Scale scaleWeird16(aWeird16, s);
    float aWeird17[] = {329, 428, 688, 1003, 1200}; //chinese lusheng
    s = 5;
    Scale scaleWeird17(aWeird17, s);
    float aWeird18[] = {178, 340, 448, 662, 888, 1102, 1200}; //chinese dizi
    s = 7;
    Scale scaleWeird18(aWeird18, s);
    float aWeird19[] = {210, 338, 498, 715, 908, 1040, 1200}; //chinese sheng
    s = 7;
    Scale scaleWeird19(aWeird19, s);
    float aWeird20[] = {170, 274, 492, 662, 878, 996, 1200}; //chinese yangqin
    s = 7;
    Scale scaleWeird20(aWeird20, s);
    float aWeird21[] = {204, 520, 638, 702, 1018, 1138, 1200}; //al farabi g2
    s = 7;
    Scale scaleWeird21(aWeird21, s);
    float aWeird22[] = {134, 400, 502, 702, 902, 934, 1200}; //arabic zanjaran
    s = 7;
    Scale scaleWeird22(aWeird22, s);
    float aWeird23[] = {200, 354, 502, 702, 902, 934, 1056, 1200}; //arabic rast on c
    s = 8;
    Scale scaleWeird23(aWeird23, s);
    
        

		Scale* scales = new Scale[24];
		scales[0] = scaleWeird;
		scales[1] = scaleWeird1;
		scales[2] = scaleWeird2;
		scales[3] = scaleWeird3;
		scales[4] = scaleWeird4;
		scales[5] = scaleWeird5;
    scales[6] = scaleWeird6;
    scales[7] = scaleWeird7;
    scales[8] = scaleWeird8;
    scales[9] = scaleWeird9;
    scales[10] = scaleWeird10;
    scales[11] = scaleWeird11;
    scales[12] = scaleWeird12;
    scales[13] = scaleWeird13;
    scales[14] = scaleWeird14;
    scales[15] = scaleWeird15;
    scales[16] = scaleWeird16;
    scales[17] = scaleWeird17;
    scales[18] = scaleWeird18;
    scales[19] = scaleWeird19;
    scales[20] = scaleWeird20;
    scales[21] = scaleWeird21;
    scales[22] = scaleWeird22;
    scales[23] = scaleWeird23;
		return scales;
	}
private:
	static int shiftIndex(int index, int shift, int arraySize) {
		return (index + shift) % arraySize;
	}
};

#endif

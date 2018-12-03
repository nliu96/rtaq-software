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
		float aWeird1[] = { 300, 500, 700, 1000, 1200 };
		s = 5;
		Scale scaleWeird1(aWeird1, s);
		float aWeird2[] = { 200, 400, 700, 900, 1200 };
		s = 5;
		Scale scaleWeird2(aWeird2, s);
		float aWeird3[] = { 200, 300, 500, 700, 800, 1000, 1200 };
		s = 7;
		Scale scaleWeird3(aWeird3, s);
		float aWeird4[] = { 200, 400, 500, 700, 900, 1100, 1200 };
		s = 7;
		Scale scaleWeird4(aWeird4, s);
		float aWeird5[] = { 200, 400, 600, 700, 900, 1100, 1200 };
		s = 7;
		Scale scaleWeird5(aWeird5, s);

		Scale* scales = new Scale[6];
		scales[0] = scaleWeird;
		scales[1] = scaleWeird1;
		scales[2] = scaleWeird2;
		scales[3] = scaleWeird3;
		scales[4] = scaleWeird4;
		scales[5] = scaleWeird5;
		return scales;
	}
private:
	static int shiftIndex(int index, int shift, int arraySize) {
		return (index + shift) % arraySize;
	}
};

#endif

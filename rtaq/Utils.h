#include "Scale.h"

#ifndef UTILS_H_
#define UTILS_H_

#pragma optimize("", off)
class Utils {
public:
	static Scale generateSubScale(Scale scale, int numNotes, int shift=0) {
		int originalScaleSize = scale.getScaleSize();
		float indexFactor = (float) originalScaleSize / numNotes;
		
		// Just return the original scale, # notes is wrong
		if (indexFactor <= 1.0) {
			return scale;
		}
		
		float* tempCentsScale = new float[numNotes];
		float* originalCentsScale = scale.getCentsScale();

		// Place equal distance indices in new array
		for (int i = 0; i < numNotes; i++) {
			int scaledIndex = (int)(i*indexFactor);
			float thaThing = 
				originalCentsScale[shiftIndex(scaledIndex, shift, originalScaleSize)];
			tempCentsScale[i] = originalCentsScale[
					shiftIndex(scaledIndex, shift, originalScaleSize)];
		}

		return Scale(tempCentsScale, numNotes);
	}
private:
	static int shiftIndex(int index, int shift, int arraySize) {
		return (index + shift) % arraySize;
	}
};

#endif

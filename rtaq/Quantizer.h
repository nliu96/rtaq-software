#include "Scale.h"

#ifndef QUANTIZER_H_
#define QUANTIZER_h_

class Quantizer {
public:
	//Quantizer() : totalNotes(5) { };
	~Quantizer() {
		//delete[] extendedScale;
	};
	Quantizer(Scale aScale) {
		this->scale = aScale;
		this->scaleSize = scale.getScaleSize();
		setExtendedScaleClass();
	};
	unsigned int quantize(float voltageScaled) {
		unsigned int output = 0;
		unsigned int curr = 0;
		for (unsigned int i = 0; i < this->totalNotes; i++) {
			curr = this->extendedScale[i];
			if (voltageScaled >= curr) {
				output = curr;
			}
		}

		return output;
	};
	int getTotalNotes() {
		return this->totalNotes;
	};
	Scale getScale() {
		return this->scale;
	}
	float* getExtendedScale() {
		return this->extendedScale;
	}
private:
	const int highDacValue = 8192;
	Scale scale;
	float * extendedScale;
	unsigned int scaleSize;
	unsigned int totalNotes;
	void setExtendedScaleClass() {
		//unsigned int highestCent = this->scale.getCentsScale()[scaleSize - 1];
		unsigned int octaves = this->highDacValue / 1200;
		this->totalNotes = octaves * scaleSize + 1;
		this->extendedScale = new float[this->totalNotes];

		extendedScale[0] = 0;
		float* aCentsScale = scale.getCentsScale();
		for (unsigned int i = 1; i < totalNotes; i++) {
			int octaveScalar = (i - 1) / scaleSize;
			extendedScale[i] = octaveScalar * 1200.0 +
				aCentsScale[(i - 1) % scaleSize];
		}
	};
};
#endif
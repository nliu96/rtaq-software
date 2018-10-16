#include "Scale.h"

class Quantizer {
public:
	//Quantizer() : totalNotes(5) { };
	~Quantizer() {
		//delete[] extendedScale;
	};
	Quantizer(unsigned int * scale, int size) {
		this->centsScale = scale;
		this->scaleSize = size;
		setExtendedScale();
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
	unsigned int * getCentsScale() {
		return this->centsScale;
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
	unsigned int * centsScale;
	float * extendedScale;
	unsigned int scaleSize;
	unsigned int totalNotes;
	void setExtendedScale() {
		/*unsigned int highestCent = 1200;// this->scale.getCentsScale()[scaleSize - 1];
		unsigned int octaves = this->highDacValue / highestCent + 1;
		this->totalNotes = ((octaves - 1) * (scaleSize - 1)) + scaleSize - 1;
		this->extendedScale = new unsigned int[this->totalNotes];

		unsigned int idx = 0;
		for (unsigned int i = 0; i < octaves - 1; i++) {
			for (unsigned int j = 0; j < scaleSize - 1; j++) {
				idx = (scaleSize - 1)*i + j;
				extendedScale[idx] = centsScale[j] + i * highestCent;
			}
		}
		for (unsigned int p = 0; p < scaleSize; p++) {
			idx = (octaves - 1) * (scaleSize - 1) + p;
			extendedScale[idx] = centsScale[p] + (octaves - 1) * highestCent;
		}*/
	};
	void setExtendedScaleClass() {
		unsigned int highestCent = this->scale.getCentsScale()[scaleSize - 1];
		unsigned int octaves = this->highDacValue / 1200;
		this->totalNotes = octaves * scaleSize + 1;
		this->extendedScale = new float[this->totalNotes];

		extendedScale[0] = 0;
		float* aCentsScale = scale.getCentsScale();
		for (int i = 1; i < totalNotes; i++) {
			int octaveScalar = i / scaleSize;
			extendedScale[i] = octaveScalar *
				aCentsScale[(i - 1) % scaleSize];
		}
	};
};
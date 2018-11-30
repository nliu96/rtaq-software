#include "Scale.h"
#include "Utils.h"

#ifndef WEIRD_H_
#define WEIRD_H_

#pragma optimize("", off)
class WeirdQuantizer {
public:
	~WeirdQuantizer() {
		delete scale;
		//for (int i = 0; i < this->numOutputs; i++) {
		//	delete[] quantizers[i].getExtendedScale();
		//}
		//delete[] quantizers[0].getExtendedScale();
		//quantizers[0].~Quantizer();
		//delete[] quantizers[1].getScale();
	};
	WeirdQuantizer(Scale* aScale, int mainScaleNotes, int quantScaleNotes, int shift=0) {
		this->scale = Utils::generateSubScale(aScale, mainScaleNotes);
		this->quantizers = new Quantizer[numOutputs];
		for (int i = 0; i < numOutputs; i++) {
			Scale* subScale = Utils::generateSubScale(this->scale, quantScaleNotes, i+shift);
			quantizers[i] = Quantizer(subScale);
			delete subScale;
		}
	};
	int getNumOutputs() {
		return this->numOutputs;
	}
	float* quantize(float* voltageScaled) {
		float* outputs = new float[this->numOutputs];
		for (int i = 0; i < numOutputs; i++) {
			outputs[i] = quantizers[i].quantize(voltageScaled[i]);
		}

		return outputs;
	}
	void set(Scale* aScale, int mainScaleNotes, int quantScaleNotes, int shift = 0) {
		delete this->scale;
		this->scale = Utils::generateSubScale(aScale, mainScaleNotes);
		//this->quantizers = new Quantizer[numOutputs];
		for (int i = 0; i < numOutputs; i++) {
			//quantizers[i].~Quantizer();
			Scale* subScale = Utils::generateSubScale(this->scale, quantScaleNotes, i + shift);
			quantizers[i] = Quantizer(subScale);
			delete subScale;
		}
	}
private:
	Quantizer* quantizers;
	Scale* scale;
	const int numOutputs = 4;
};

#endif

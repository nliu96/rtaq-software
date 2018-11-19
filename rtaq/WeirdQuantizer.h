#include "Scale.h"
#include "Utils.h"

#ifndef WEIRD_H_
#define WEIRD_H_

#pragma optimize("", off)
class WeirdQuantizer {
public:
	~WeirdQuantizer() {
		
	};
	WeirdQuantizer(Scale* aScale, int mainScaleNotes, int quantScaleNotes, int shift) {
		this->scale = Utils::generateSubScale(aScale, mainScaleNotes);
		this->quantizers = new Quantizer[numOutputs];
		for (int i = 0; i < numOutputs; i++) {
			Scale* subScale = Utils::generateSubScale(this->scale, quantScaleNotes, i+shift);
			quantizers[i] = Quantizer(subScale);
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
private:
	Quantizer* quantizers;
	Scale* scale;
	const int numOutputs = 4;
};

#endif

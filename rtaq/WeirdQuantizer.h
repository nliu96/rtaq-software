#include "Scale.h"
#include "Utils.h"

#ifndef WEIRD_H_
#define WEIRD_H_

#pragma optimize("", off)
class WeirdQuantizer {
public:
	~WeirdQuantizer() {

	};
	WeirdQuantizer(Scale aScale, int mainScaleNotes, int quantScaleNotes) {
		this->scale = Utils::generateSubScale(aScale, mainScaleNotes);
		this->quantizers = new Quantizer[numOutputs];
		for (int i = 0; i < numOutputs; i++) {
			quantizers[0] = Quantizer(
				Utils::generateSubScale(this->scale, quantScaleNotes, i));
		}
	};
	int getNumOutputs() {
		return this->numOutputs;
	}
private:
	Quantizer* quantizers;
	Scale scale;
	const int numOutputs = 4;
};

#endif
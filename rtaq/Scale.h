class Scale {
public:
	~Scale() {
		delete[] centsScale;
		delete[] midiScale;
	};
	Scale() {
		this->centsScale = new float[3]{ 5.0, 5.0, 5.0 };
		this->midiScale = new unsigned int[3]{ 5, 5, 5 };
	};
	Scale(float * cents, int size) {
		// Make sure there is no 0 or neg values
		this->scaleSize = size;
		if (cents[0] == 0) {
			this->scaleSize = size - 1;
			centsScale = new float[scaleSize];
			for (int i = 0; i < size; i++) {
				centsScale[i] = cents[i + 1];
			}
		} else {
			centsScale = new float[scaleSize];
			for (int i = 0; i < size; i++) {
				centsScale[i] = cents[i];
			}
		}
	};
	int getScaleSize() {
		return this->scaleSize;
	};
private:
	float* centsScale;
	unsigned int * midiScale;
	int scaleSize;
};

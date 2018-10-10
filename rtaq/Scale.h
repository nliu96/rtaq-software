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
private:
	float* centsScale;
	unsigned int * midiScale;
	unsigned int scaleSize;
};

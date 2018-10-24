#ifndef SCALE_H_
#define SCALE_H_

class Scale {
public:
	~Scale() {
		//delete[] centsScale;
		//delete[] midiScale;
	};
	Scale() {
		this->centsScale = new float[3]{ 5.0, 5.0, 5.0 };
		this->midiScale = new unsigned int[3]{ 5, 5, 5 };
	};
	Scale(float * cents, int size) {
		// Simply append 1200 to ensure root
		this->scaleSize = size + 1;
		
		this->centsScale = new float[scaleSize];
		for (size_t i = 0; i < scaleSize - 1; i++) {
			centsScale[i] = cents[i];
		}
		centsScale[scaleSize - 1] = 1200.0;
		this->sortScale();
		this->removeBadNotes();
	};
	Scale(char* scalaString, int charLength) {
		// Note: strings are 0 terminated (last value is 0)
		int currChar = 0;
		int currValidLine = 0; // Keep track of relevant (non-comment) lines
		
		//TODO: kev, this is messed up..
		// First line: just a title (ignore)
		while (currChar < charLength) {
			if (scalaString[currChar] != '!') {
				currValidLine++; // This implies line is the title
			} else if (scalaString[currChar] == '\n') {
				currChar++;
				break;
			}
			currChar++;
		}

		// Next line: should be # of notes
		while (currChar < charLength) {
			if (scalaString[currChar] != '!') {
				currValidLine++;
			}
			else if (scalaString[currChar] == '\n') {
				currChar++;
				break;
			}
			currChar++;
		}

		this->scaleSize = 69;
	}
	int getScaleSize() {
		return this->scaleSize;
	};
	float* getCentsScale() {
		return this->centsScale;
	} 
private:
	float* centsScale;
	unsigned int * midiScale;
	int scaleSize;
	void sortScale() {
		// bubble sort it
		for (int j = scaleSize - 1; j > 0; j--) {
			bool swapped = false;
			for (int i = 0; i < j; i++) {
				if (centsScale[i] > centsScale[i + 1]) {
					float temp = centsScale[i + 1];
					centsScale[i + 1] = centsScale[i];
					centsScale[i] = temp;
					swapped = true;
				}
			}
			if (!swapped) {
				break;
			}
		}
	};
	void removeBadNotes() {
		// Remove negatives, zeros, above 1200, duplicates
		float prevVal = 0;
		int *indices = new int[scaleSize];
		int iInd = 0;
		// Loop and note which to remove
		for (int i = 0; i < scaleSize; i++) {
			float curr = centsScale[i];
			if (curr <= 0 || curr == prevVal || curr > 1200.0) {
				indices[iInd] = i;
				iInd++;
			}

			prevVal = curr;
		}

		// Create a new corrected array
		if (iInd > 0) {
			float* tempArray = new float[scaleSize - iInd];
			int currIndiceIndex = 0;
			int currTempIndex = 0;
			for (int i = 0; i < scaleSize; i++) {
				if (i == indices[currIndiceIndex]) {
					currIndiceIndex++;	// Simply skip..
				} else {
					tempArray[currTempIndex] = this->centsScale[i];
					currTempIndex++;
				}
			}

			delete[] this->centsScale;
			this->centsScale = tempArray;
			this->scaleSize = scaleSize - iInd;
		}
		delete[] indices;
	};
};
#endif
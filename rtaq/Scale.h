#ifndef SCALE_H_
#define SCALE_H_

#pragma optimize("", off)
class Scale {
public:
	~Scale() {
		//delete[] centsScale;
		//delete[] midiScale;
	};
	Scale() {

	};
	Scale(float * cents, int size, bool hasRoot=true) {
		// Simply append 1200 to ensure root
		if (hasRoot) {
			this->scaleSize = size + 1;

			this->centsScale = new float[scaleSize];
			for (int i = 0; i < scaleSize - 1; i++) {
				centsScale[i] = cents[i];
			}
			centsScale[scaleSize - 1] = 1200.0;
		} else {
			this->scaleSize = size;

			this->centsScale = new float[scaleSize];
			for (int i = 0; i < scaleSize; i++) {
				centsScale[i] = cents[i];
			}
		}
		this->sortScale();
		this->removeBadNotes();
	};
	Scale(char* scalaString, int charLength) {
		// Note: strings are 0 terminated (last value is 0)
		int currChar = 0;
		int currValidLine = 0; // Keep track of relevant (non-comment) lines
		
		// First line: just a title (don't need to store it)
		bool isFirstCharOfLine = true;
		while (currChar < charLength - 1) { // Strings are 0-terminated, so ignore last char
			// If title already done, break, else keep checking
			if (scalaString[currChar] == '\n') {
				if (currValidLine == 1) {
					currChar++;
					break;
				}
				isFirstCharOfLine = true;
				currChar++;
				continue;
			}

			if (scalaString[currChar] != '!' && isFirstCharOfLine) {
				// This implies line is the title
				currValidLine++;
			} 

			isFirstCharOfLine = false;
			currChar++;
		}

		// Next line: should be # of notes
		isFirstCharOfLine = true;
		int numberOfNotesArray[2] = { 0, 0 };
		int notesArrayIndex = 1;
		while (currChar < charLength - 1) {
			if (scalaString[currChar] == '\n') {
				if (currValidLine == 2) {
					currChar++;
					break;
				}
				isFirstCharOfLine = true;
				currChar++;
				continue;
			}

			if (scalaString[currChar] != '!' && isFirstCharOfLine) {
				currValidLine++;
			} 

			// If on valid line, note the #
			if (currValidLine == 2 && notesArrayIndex != -1) {
				numberOfNotesArray[notesArrayIndex] = scalaString[currChar] - '0';
				notesArrayIndex--;
			}

			isFirstCharOfLine = false;
			currChar++;
		}
		int firstNumberTotal = notesArrayIndex == -1 
			? 10 * numberOfNotesArray[1] : numberOfNotesArray[1];
		int numberOfNotes =  numberOfNotesArray[0] + firstNumberTotal;
		
		// The rest of the lines are pitch values (or comments)
		this->scaleSize = numberOfNotes + 1; // add 1 so we can append 1200.0
		this->centsScale = new float[scaleSize];
		char* noteBuffer = new char[10]; // max size 10
		int bufferIndex = 0, noteIndex = 0;
		isFirstCharOfLine = true;
		bool shouldAddNote = false;
		bool containedPeriod = false;
		while (currChar < charLength - 1 && noteIndex < numberOfNotes) {
			if (shouldAddNote) {
				this->centsScale[noteIndex] = charBufferToNote(noteBuffer, bufferIndex, containedPeriod);
				noteIndex++;
				noteBuffer = new char[10];
				bufferIndex = 0;
				shouldAddNote = false;
				containedPeriod = false;
				continue;
			}
			if (scalaString[currChar] == '\n') {
				shouldAddNote = true;
				isFirstCharOfLine = true;
				currChar++;
				continue;
			}

			if (scalaString[currChar] != '!' && isFirstCharOfLine) {
				currValidLine++;
			}

			// If on valid line append to note buffer
			if (currValidLine >= 3 && bufferIndex < 10) {
				noteBuffer[bufferIndex] = scalaString[currChar];
				if (scalaString[currChar] == '.') {
					containedPeriod = true;
				}
				bufferIndex++;
			}

			isFirstCharOfLine = false;
			currChar++;
		}
		// Add the last note (necessary if no new lines after pitch value)
		if (noteIndex < numberOfNotes) {
			this->centsScale[noteIndex] = charBufferToNote(noteBuffer, bufferIndex, containedPeriod);
			noteIndex++;
		}

		// Fill rest of array to 1200
		while (noteIndex < scaleSize) {
			this->centsScale[noteIndex] = 1200.0;
			noteIndex++;
		}
		// Cleanup the scale (same as constructor);
		this->sortScale();
		this->removeBadNotes();
	}
	int getScaleSize() {
		return this->scaleSize;
	};
	float* getCentsScale() {
		return this->centsScale;
	} 
private:
	float* centsScale;
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
	float charBufferToNote(char* charBuffer, int length, bool containedPeriod) {
		float leftOperatorTotal = 0.0;
		float rightOperatorTotal = 0.0;
		int operatorIndex = -1;
		float* currTotal = &leftOperatorTotal;
		float multiplier = 10.0;
		// Note what is to the right/left of the operator
		for (int i = 0; i < length; i++) {
			// Do nothing if it's whitespace
			if (charBuffer[i] == ' ') { continue; }
			if (charBuffer[i] == '.' || charBuffer[i] == '/') {
				operatorIndex = i;
				currTotal = &rightOperatorTotal;
				continue;
			}
			*currTotal *= multiplier;
			*currTotal += charBuffer[i] - '0';
		}

		// Add or divide based on cent value or if it is a ratio
		float output;
		if (operatorIndex != -1 && containedPeriod) {
			output = leftOperatorTotal +
				rightOperatorTotal / getPowerOf10(length - operatorIndex - 1);
		} else if (operatorIndex != -1) {
			output = 1200.0 * (leftOperatorTotal / rightOperatorTotal);
		} else if (containedPeriod) {
			output = leftOperatorTotal;
		} else {
			output = 1200.0 * leftOperatorTotal;
		}

		return output;
	}
	float getPowerOf10(int val) {
		float start = 10.0;
		int scalar = 1;
		if (val == 0) {
			return 1.0;
		} else if (val < 0) {
			scalar = -1;
		}

		for (int i = 1; i < val; val = val + scalar) {
			start *= scalar == 1 ? 10 : 0.1;
		}
		return start;
	}
};
#endif
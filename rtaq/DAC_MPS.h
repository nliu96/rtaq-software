#include "Arduino.h"

class DAC_MPS
{
  public:
    DAC_MPS(byte channel, int slaveSelectPin)
	{
		this->channel = channel;
		this->slaveSelectPin = slaveSelectPin;
		pinMode(slaveSelectPin, OUTPUT);
	};
    ~DAC_MPS() { };
    void setOutput(unsigned int val)
	{
		DAC_MPS::setOutput(val, this->GAIN_2);
	};
    void setOutput(unsigned int val, byte gain) {
		byte lowByte = val & 0xff;
		byte highByte = ((val >> 8) & 0xff)
			| this->channel << 7 | gain << 5 | this->shutdown << 4;

		digitalWrite(this->slaveSelectPin, LOW);
		SPI.transfer(highByte);
		SPI.transfer(lowByte);
		digitalWrite(this->slaveSelectPin, HIGH);
	};

  private:
    const int GAIN_1 = 0x1;
    const int GAIN_2 = 0x0;
    const int shutdown = 1;
    byte channel;
    int slaveSelectPin;
};

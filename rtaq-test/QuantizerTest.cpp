#include "pch.h"

TEST(Quant, TestScales) {
	unsigned int expected[] = { 0, 1200, 2400, 3600, 4800, 6000, 7200 };
	unsigned int out[] = { 0, 1200, 2400, 3600, 4800, 6000, 7200, 7200 };
	unsigned int toQuant[] = { 1, 1201, 2401, 3601, 4801, 6001, 7201, 8500 };
	unsigned int a[] = { 0, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	int expectedSize = sizeof(expected) / sizeof(expected[0]);
	int outSize = sizeof(out) / sizeof(out[0]);
	Quantizer q = Quantizer(a, aSize);
	// Error: 0 and 1200 end up with the same. We should pre-process + assume
	// that they are going to be the same note (so this array should
	// have a scale size of just 1.
	ASSERT_EQ(q.getTotalNotes(), expectedSize);
	
	for (int i = 0; i < outSize; i++) {
		EXPECT_EQ(out[i], q.quantize(toQuant[i]));
	}
}

TEST(Quant, ScaleClass) {
	float a[] = { 0, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale scale = Scale(a, aSize);
	Quantizer quantizer = Quantizer(scale);

	ASSERT_EQ(scale.getScaleSize(), 1);
	ASSERT_EQ(quantizer.getTotalNotes(), 7);

	unsigned int expected[] = { 0, 1200, 2400, 3600, 4800, 6000, 7200 };
	int expectedSize = sizeof(expected) / sizeof(expected[0]);
	for (int i = 0; i < expectedSize; i++) {
		EXPECT_EQ(quantizer.getExtendedScale()[i], expected[i]);
	}
}
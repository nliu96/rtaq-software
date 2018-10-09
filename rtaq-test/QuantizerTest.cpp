#include "pch.h"

TEST(Scale, TestScales) {
	unsigned int out[] = { 0, 1200, 2400, 3600, 4800, 6000, 7200 };
	unsigned int toQuant[] = { 1, 1201, 2401, 3601, 4801, 6001, 7201 };
	unsigned int a[] = { 0, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	int outSize = sizeof(out) / sizeof(out[0]);
	Quantizer q = Quantizer(a, aSize);
	
	ASSERT_EQ(q.getTotalNotes(), outSize);
	
	for (int i = 0; i < outSize; i++) {
		EXPECT_EQ(out[i], q.quantize(toQuant[i]));
	}
}
#include "pch.h"

TEST(Scale, TestScales) {
	float a[] = { -1, 0.0, 300.0, -5, 1200.0, 1400 };
	float expected[] = { 300.0, 1200.0 };
	int aSize = sizeof(a) / sizeof(a[0]);
	int expSize = sizeof(expected) / sizeof(expected[0]);
	Scale scale = Scale(a, aSize);
	// Error: 0 and 1200 end up with the same. We should pre-process + assume
	// that they are going to be the same note (so this array should
	// have a scale size of just 1.
	ASSERT_EQ(scale.getScaleSize(), expSize);
	float* centsScale = scale.getCentsScale();
	for (int i = 0; i < scale.getScaleSize(); i++) {
		EXPECT_EQ(centsScale[i], expected[i]);
	}
}
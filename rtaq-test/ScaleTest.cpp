#include "pch.h"

TEST(Scale, TestScales) {
	float a[] = { 0.0, 1200.0 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale scale = Scale(a, aSize);
	// Error: 0 and 1200 end up with the same. We should pre-process + assume
	// that they are going to be the same note (so this array should
	// have a scale size of just 1.
	ASSERT_EQ(scale.getScaleSize(), 2);
}
#include "pch.h"

#pragma optimize("", off)
TEST(Scale, TestScales) {
	float a[] = { -1, 0.0, 300.0, -5, 1200.0, 1400, 1200.0 };
	float expected[] = { 300.0, 1200.0 };
	int aSize = sizeof(a) / sizeof(a[0]);
	int expSize = sizeof(expected) / sizeof(expected[0]);
	Scale scale = Scale(a, aSize);

	ASSERT_EQ(scale.getScaleSize(), expSize);
	float* centsScale = scale.getCentsScale();
	for (int i = 0; i < scale.getScaleSize(); i++) {
		EXPECT_EQ(centsScale[i], expected[i]);
	}
}

TEST(Scale, TestScales2) {
	float a[] = { 1200.0, 1200.0, 1200.0, 1200.0 };
	float expected[] = { 1200.0 };
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

TEST(Scale, TestScales3) {
	float a[] = { 345.1, -500, 4392, 590, 4, 1200, 0 };
	float expected[] = { 4, 345.1, 590, 1200 };
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

TEST(Scale, TestScales4) {
	float a[] = { 300.0, 1200.0 };
	float expected[] = { 300.0, 1200.0 };
	int aSize = sizeof(a) / sizeof(a[0]);
	int expSize = sizeof(expected) / sizeof(expected[0]);
	Scale scale = Scale(a, aSize);

	ASSERT_EQ(scale.getScaleSize(), expSize);
	float* centsScale = scale.getCentsScale();
	for (int i = 0; i < scale.getScaleSize(); i++) {
		EXPECT_EQ(centsScale[i], expected[i]);
	}
}

TEST(Scale, TestScales5) {
	float a[] = { 0.0 };
	float expected[] = { 1200 };
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
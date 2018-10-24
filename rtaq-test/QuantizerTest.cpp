#include "pch.h"

#pragma optimize("", off)
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
TEST(Quant, Scale) {
	float a[] = { 300.0, 1200.0 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale scale = Scale(a, aSize);
	Quantizer quantizer = Quantizer(scale);

	ASSERT_EQ(scale.getScaleSize(), 2);
	ASSERT_EQ(quantizer.getTotalNotes(), 13);

	float expected[] = { 0, 300, 1200, 1500, 2400, 2700, 3600, 3900, 4800, 5100, 6000, 6300, 7200 };
	int expectedSize = sizeof(expected) / sizeof(expected[0]);
	for (int i = 0; i < expectedSize; i++) {
		float test = quantizer.getExtendedScale()[i];
		EXPECT_EQ(quantizer.getExtendedScale()[i], expected[i]);
	}
}

TEST(Quant, Scale1) {
	float a[] = { 300.0, 500.0 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale scale = Scale(a, aSize);
	Quantizer quantizer = Quantizer(scale);

	float expected[] = { 0, 300, 500, 1200, 1500, 1700, 2400, 2700, 2900, 3600, 3900, 4100, 4800, 5100, 5300, 6000, 6300, 6500, 7200 };
	int expectedSize = sizeof(expected) / sizeof(expected[0]);
	ASSERT_EQ(scale.getScaleSize(), 3);
	ASSERT_EQ(quantizer.getTotalNotes(), expectedSize);

	for (int i = 0; i < expectedSize; i++) {
		float test = quantizer.getExtendedScale()[i];
		EXPECT_EQ(quantizer.getExtendedScale()[i], expected[i]);
	}
}

TEST(Quant, Scale2) {
	float a[] = { 0.0, 300, 500, 700, 1000, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale scale = Scale(a, aSize);
	Quantizer quantizer = Quantizer(scale);

	float expected[] = { 0.0, 300, 500, 700, 1000, 1200,
							1500, 1700, 1900, 2200, 2400,
							2700, 2900, 3100, 3400, 3600,
							3900, 4100, 4300, 4600, 4800,
							5100, 5300, 5500, 5800, 6000,
							6300, 6500, 6700, 7000, 7200 };
	int expectedSize = sizeof(expected) / sizeof(expected[0]);
	ASSERT_EQ(scale.getScaleSize(), 5);
	ASSERT_EQ(quantizer.getTotalNotes(), expectedSize);

	for (int i = 0; i < expectedSize; i++) {
		EXPECT_EQ(quantizer.getExtendedScale()[i], expected[i]);
	}
}

TEST(Quant, QuantizeScale2) {
	float a[] = { 0.0, 300, 500, 700, 1000, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale scale = Scale(a, aSize);
	Quantizer quantizer = Quantizer(scale);

	float expected[] = { 0.0, 300, 500, 700, 1000, 1200,
							1500, 1700, 1900, 2200, 2400,
							2700, 2900, 3100, 3400, 3600,
							3900, 4100, 4300, 4600, 4800,
							5100, 5300, 5500, 5800, 6000,
							6300, 6500, 6700, 7000, 7200 };
	int expectedSize = sizeof(expected) / sizeof(expected[0]);
	ASSERT_EQ(scale.getScaleSize(), 5);
	ASSERT_EQ(quantizer.getTotalNotes(), expectedSize);

	for (int i = 0; i < expectedSize; i++) {
		EXPECT_EQ(quantizer.quantize(expected[i]), expected[i]);
	}
}
#pragma optimize("", on)
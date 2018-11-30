#include "pch.h"

#pragma optimize("", off)

TEST(UtilsTest, Basic) {
	float a[] = { 100, 200, 300, 400, 500, 
		600, 700, 800, 900, 1000, 1100, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale* sc = Utils::generateSubScale(&Scale(a, aSize), 4);
	EXPECT_EQ(4 , sc->getScaleSize()); // b/c 1200 is appended..
}

TEST(UtilsTest, Basic1) {
	float a[] = { 100, 200, 300, 400, 500,
		600, 700, 800, 900, 1000, 1100, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale* sc = Utils::generateSubScale(&Scale(a, aSize), 7);
	Scale* sc0 = Utils::generateSubScale(&Scale(a, aSize), 7, 0);
	Scale* sc1 = Utils::generateSubScale(&Scale(a, aSize), 7, 1);
	Scale* sc2 = Utils::generateSubScale(&Scale(a, aSize), 7, 2);
	Scale* sc3 = Utils::generateSubScale(&Scale(a, aSize), 7, 3);
	Scale* sc4 = Utils::generateSubScale(&Scale(a, aSize), 7, 13);
	EXPECT_EQ(7, sc->getScaleSize()); // b/c 1200 is appended..
}

TEST(WeirdQuant, Basic) {
	float a[] = { 100, 200, 300, 400, 500,
		600, 700, 800, 900, 1000, 1100, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale sc = Scale(a, aSize);
	WeirdQuantizer q = WeirdQuantizer(&sc, 7, 5);
	q.set(&sc, 7, 5);
	EXPECT_EQ(1, 1); // We just want it to run
}

TEST(WeirdQuant, Quantizing) {
	float a[] = { 200, 400, 500, 700,
		900, 1100, 1200 };
	int aSize = sizeof(a) / sizeof(a[0]);
	Scale sc = Scale(a, aSize);
	WeirdQuantizer q = WeirdQuantizer(&sc, 6, 3);
	
	for (int i = 0; i < aSize; i++) {
		float o[] = { a[i], a[i], a[i], a[i] };
		float* quantized = q.quantize(o);
		float uh0 = quantized[0];
		float uh1 = quantized[1];
		float uh2 = quantized[2];
		float uh3 = quantized[3];
		float uh4 = quantized[3];
	}
	EXPECT_EQ(1, 1);
}

#include "svpng.inc"
#include <iostream>
#include <stdio.h>
#include "basic.h"

#define W 512
#define H 512

unsigned char img[W * H * 3];

int main() {
	unsigned char* p = img;
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++, p += 3)
			p[0] = p[1] = p[2] = (int)(fminf(sample(
			(float)x / W, (float)y / H) * 255.0f, 255.0f));
	FILE * fp = NULL;
	fopen_s(&fp, "basic.png", "wb");
	svpng(fp, W, H, img, 0);
	return 0;
}
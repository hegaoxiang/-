#pragma once

#include <math.h>
#include <stdlib.h>
#define TWO_PI 6.28f

#define N 64
#define MAX_STEP 10
#define MAX_DISTANCE 2.0f
#define EPSILON 1e-6


// ...
typedef struct
{
	float sd;
	float emissive;
}Result;
Result unionOp(Result a, Result b);
Result scene(float x, float y);
float sample(float x, float y);
float trace(float ox, float oy, float dx, float dy);
float circleSDF(float x, float y, float cx, float cy, float r);



float circleSDF(float x, float y, float cx, float cy, float r)
{
	float ux = x - cx;
	float uy = y - cy;
	return sqrtf(ux * ux + uy * uy) - r;
}

float trace(float ox, float oy, float dx, float dy)
{
	float t = 0.0f;
	for (int i = 0; i < MAX_STEP && t < MAX_DISTANCE; i++)
	{
		Result r = scene(ox + dx * t, oy + dy * t);
		if (r.sd < EPSILON)
			return r.emissive;
		t += r.sd;
	}
	return 0.0f;
}

Result unionOp(Result a, Result b)
{
	return (a.sd < b.sd) ? a : b;
}

Result scene(float x, float y)
{
	Result r = {
		circleSDF(x, y, 0.5f, 0.5f, 0.1f),
		2.0f
	};
	//Result r1 = {
	//	circleSDF(x, y, 0.2f, 0.2f, 0.1f),
	//	0.2f
	//};
	return r;
}

float sample(float x, float y)
{
	float sum = 0.0f;
	for (int i = 0; i < N; i++)
	{
		float a = TWO_PI * (i + (float)rand()) / RAND_MAX;
		sum += trace(x, y, cosf(a), sinf(a));
	}
	return sum;
}

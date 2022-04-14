#pragma once
#include <random>
#include <stdlib.h>
#include <iostream>//for debbuging

#define CANVAS_WIDTH 1200
#define CANVAS_HEIGHT 600

#define PLAYER_WIDTH_RANGE 1000
#define PLAYER_HEIGTH_RANGE 550

#define ASSET_PATH ".\\assets\\"

#define PLAYER_SIZE 60.0f

#define SETCOLOR(c,r,g,b){c[0] = r; c[1] = g; c[2] = b;}
#define RAND0TO1()(rand()/(float)RAND_MAX)

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

struct Disk
{
	float cx;
	float cy;
	float radius;
};
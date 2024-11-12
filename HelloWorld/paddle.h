#pragma once
#include "constants.h"
#include "Play.h"
struct Paddle {
	Play::Vector2D pos = { DISPLAY_WIDTH / 2, 32 };
};
//struct Paddle paddle;

void DrawPaddle(const Paddle& paddle);
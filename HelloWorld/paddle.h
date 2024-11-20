#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "constants.h"
#include "Play.h"

struct Paddle {
	Play::Vector2D pos = { DISPLAY_WIDTH / 2, 16};
};

void DrawPaddle(const Paddle& paddle);
bool IsColliding(const Paddle& paddle, const Play::GameObject& ball);
void UpdatePaddle(Paddle& paddle);
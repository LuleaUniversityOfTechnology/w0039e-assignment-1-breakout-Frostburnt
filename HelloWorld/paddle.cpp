#include "paddle.h"

void DrawPaddle(const Paddle& paddle) {
	Play::Vector2D bl = { paddle.pos.x - 40, paddle.pos.y - 7 };
	Play::Vector2D tr = { paddle.pos.x + 40, paddle.pos.y + 7 };
	Play::DrawRect(bl, tr, Play::cBlue, true);
}
#include "paddle.h"
//paddleHeight and paddleWidth are half the actual value, measured from the origin
void DrawPaddle(const Paddle& paddle) {
	Play::Vector2D bl = { paddle.pos.x - paddleLen, paddle.pos.y - paddleHeight };
	Play::Vector2D tr = { paddle.pos.x + paddleLen, paddle.pos.y + paddleHeight };
	Play::DrawRect(bl, tr, Play::cBlue, true);
}
//sets the paddle origin point to it's self, or the edge of the window 
void UpdatePaddle(Paddle& paddle) {
		
	paddle.pos.x = std::max((paddle.pos.x - paddleSpeed * (Play::KeyDown(Play::KEY_LEFT))), 0.0f);
	paddle.pos.x = std::min((paddle.pos.x + paddleSpeed * (Play::KeyDown(Play::KEY_RIGHT))), float(DISPLAY_WIDTH));
}

bool IsColliding(const Paddle& paddle, const Play::GameObject& obj) {
	Play::Vector2D paddleTopLeft = { (paddle.pos.x - paddleLen), (paddle.pos.y + paddleHeight)};
	Play::Vector2D paddleBottomRight = { (paddle.pos.x + paddleLen), (paddle.pos.y - paddleHeight) };

	const float dx = obj.pos.x - std::max(paddleTopLeft.x, std::min(obj.pos.x, paddleBottomRight.x));
	const float dy = obj.pos.y - std::max(paddleTopLeft.y, std::min(obj.pos.y, paddleBottomRight.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}
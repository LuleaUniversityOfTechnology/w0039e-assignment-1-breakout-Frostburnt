#pragma once
const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 360;
const int DISPLAY_SCALE = 2; 
const float ballSpeed = 6.0f;
const int paddleSpeed = 7;
//paddleHeight and paddleWidth are half the actual value, measured from the origin
const int paddleLen = 40;
const int paddleHeight = 7;

enum ObjectType {
	TYPE_BALL,
	TYPE_BRICK
};

#define PLAY_USING_GAMEOBJECT_MANAGER
#define PLAY_IMPLEMENTATION
#include "Play.h"
//#include "game.h"
#include "constants.h"
#include "paddle.h"

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
};
//SetupScene spawns bricks row by row, and also sets the origin point for sprites
void SetupScene(int numrows) {
	Play::CentreSpriteOrigin("brick"); //for more accurate collisions, the hitbox should be in the center
	Play::CentreSpriteOrigin("ball");
	for (int i = 31; i < DISPLAY_WIDTH - 16; i += 17) {
		for (int j = 1; j <= numrows; j++) { 
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { i, DISPLAY_HEIGHT - 16 - 11 * j }, 7, "brick");
	}
			}

}

//Step Frame, for each frame we take another step in the simulation
//loop through all the balls, update thier position, then render them
//we pass the paddle in here so we can add it to the collision check for balls
void StepFrame(Paddle& paddle) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int objectId : ballIds){						//works like a python for loop of "for object in vector"
		GameObject& ball = Play::GetGameObject(objectId);  //
		//ball.velocity.y *= 0.7f; //used to test x axis clipping
		//ball.velocity.x *= 0.7f;  //used to test y axis clipping
		
		Play::UpdateGameObject(ball);
		// if ball hits window edges it will swap across the approprate axis
		if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0) 
			ball.velocity.x *=  - 1;
		if (ball.pos.y > DISPLAY_HEIGHT || ball.pos.y < 0)
			ball.velocity.y *= -1;
		//if ball hits paddle we swap which axis the ball is moving across
		if (IsColliding(paddle, ball))
			ball.velocity.y *= -1;
		//checks if colliding with bricks below
	
		for (int objectId : brickIds) {
			GameObject& brick = Play::GetGameObject(objectId);
			
			if (Play::IsColliding(brick, ball)) {
				Play::Vector2D diffball = ball.pos - brick.pos;			//the x and y components of a vector between brick and ball can be used to determine where the ball is approaching from
				if (abs(diffball.x) - 2 > abs(diffball.y))				//the -2 is to take into account for the round hitbox, not 100% accurate still, but cheaper than sprite collisions
					ball.velocity.x *= -1;								// we flip the balls velocity  on one axis depending on which quadrant the ball is in relative to the brick
				else
					ball.velocity.y *= -1;
	
				Play::DestroyGameObject(objectId);
			}
		}
		Play::DrawObject(ball); 
	}
	
	for (int objectId : brickIds) {
		GameObject& brick = Play::GetGameObject(objectId);
		Play::DrawObject(brick);
	}
}

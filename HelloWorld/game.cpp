#define PLAY_USING_GAMEOBJECT_MANAGER
#define PLAY_IMPLEMENTATION
#include "Play.h"
//#include "game.h"
#include "constants.h"
void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
};
//SetupScene spawns bricks row by row
void SetupScene(int numrows) {
	Play::CentreSpriteOrigin("brick");
	Play::CentreSpriteOrigin("ball");
	for (int i = 16; i < DISPLAY_WIDTH; i += 16) {
		for (int j = 1; j <= numrows; j++) { 
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { i, DISPLAY_HEIGHT - 16 * j }, 7, "brick");
	}
			}

}
//Step Frame, for each frame we take another step in the simulation
//loop through all the balls, update thier position, then render them
void StepFrame(/*float timex*/) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int objectId : ballIds){						//works like a python for loop of "for object in vector"
		GameObject& ball = Play::GetGameObject(objectId);  //
		//ball.velocity.y *= 0.7f; //used to test x axis clipping
		//ball.velocity.x *= 0.7f;  //used to test y axis clipping
		
		Play::UpdateGameObject(ball);
		//checks window borders below
		if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0) 
			ball.velocity.x *=  - 1;
		if (ball.pos.y > DISPLAY_HEIGHT || ball.pos.y < 0)
			ball.velocity.y *= -1;
		//checks if colliding with bricks below
		for (int objectId : brickIds) {
			GameObject& brick = Play::GetGameObject(objectId);
			//we flip the balls velocity  on one axis depending on which quadrant the ball is in relative to the brick
			if (Play::IsColliding(brick, ball)) {
				Play::Vector2D diffball = ball.pos - brick.pos;
				if (abs(diffball.x) > abs(diffball.y))
					ball.velocity.x *= -1;
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

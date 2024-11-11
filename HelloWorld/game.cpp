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
//Step Frame, for each frame we take another step in the simulation
//loop through all the balls, update thier position, then render them
void StepFrame(/*float timex*/) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int objectId : ballIds){						//works like a python for loop of "for object in vector"
		GameObject& ball = Play::GetGameObject(objectId);
		//ball.velocity.y *= 0.7f; //used to test x axis clipping
		//ball.velocity.x *= 0.7f;  //used to test y axis clipping
		
		Play::UpdateGameObject(ball);
		if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0) 
			ball.velocity.x *=  - 1;
		if (ball.pos.y > DISPLAY_HEIGHT || ball.pos.y < 0)
			ball.velocity.y *= -1;


		Play::DrawObject(ball); 
	}
}

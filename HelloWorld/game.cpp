#define PLAY_USING_GAMEOBJECT_MANAGER
#define PLAY_IMPLEMENTATION
#include "Play.h"
//#include "game.h"
#include "constants.h"
void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, 4, "ball");
};

void StepFrame(/*float timex*/) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int i : ballIds){						//works like a python for loop of "for item in list"
		Play::DrawObject(Play::GetGameObject(i)); 
	}
}

#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "constants.h"
#include "paddle.h"
#include "Play.h"
struct DynArray {
	//currently static
	int size;
	unsigned int scores[5];
	DynArray() {
		//loadfromfile
		this->size = 5;
		unsigned int scores[5] = { 0, 0, 0, 0 ,0 };
	};
	
	//void ordered_add(int i) {
		
	/*}
	void load() {

	}*/

};
void SetupScene(int numrows);
void SpawnBall();
void StepFrame(Paddle& paddle, unsigned int *currentscore);
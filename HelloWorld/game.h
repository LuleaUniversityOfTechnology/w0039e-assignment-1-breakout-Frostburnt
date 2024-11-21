#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "constants.h"
#include "paddle.h"
#include "Play.h"
void SetupScene(int numrows);
void SpawnBall();
void StepFrame(Paddle& paddle);
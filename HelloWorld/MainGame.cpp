#include "game.h"
#include "paddle.h"
Paddle paddle;
// The entry point for a PlayBuffer program

void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	loadscores();
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	
	SetupScene(7);
	SpawnBall();
	

}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{	
	
	Play::ClearDrawingBuffer( Play::cBlack );
	//Play::DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Hello World!" );	
	StepFrame(paddle);
	DrawPaddle(paddle);
	UpdatePaddle(paddle);
	Play::PresentDrawingBuffer();
	return Play::KeyDown( Play::KEY_ESCAPE );

}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	savescores();
	Play::DestroyManager();
	return PLAY_OK;
}


#include "game.h"
#include "paddle.h"
#include <fstream>
Paddle paddle;
DynArray highscores;
unsigned int score = 0;
// The entry point for a PlayBuffer program
void FileToArray() {
	std::fstream file("Highscores.txt");
	if (!file.is_open()) {
		unsigned int arr[5] = {};
		return;
		
		std::string line;
		while (std::getline(file, line)) {
			std::stoi(line);
		}

	}
}

void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	
	SetupScene(7);
	SpawnBall();
	

}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{	
	
	Play::ClearDrawingBuffer( Play::cBlack );
	//Play::DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Hello World!" );	
	StepFrame(paddle,  &score);
	DrawPaddle(paddle);
	UpdatePaddle(paddle);
	Play::PresentDrawingBuffer();
	if (Play::KeyDown(Play::KEY_E))
		FileToArray();
	return Play::KeyDown( Play::KEY_ESCAPE );

}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}


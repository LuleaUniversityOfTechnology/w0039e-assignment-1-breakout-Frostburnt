#define PLAY_USING_GAMEOBJECT_MANAGER
#define PLAY_IMPLEMENTATION
#include "Play.h"
//#include "game.h"
#include "constants.h"
#include "paddle.h"

unsigned int currentscore = 0;
//this should be moved to a seperate cpp/h file later
class ArrayOfUints {								//Basically an array for unsigned intergers
	public:
		
		ArrayOfUints() {
			data = new unsigned int[capacity];
		}	
		~ArrayOfUints() {
			delete[] data;
		}
		void sort_back(unsigned int value) {	//sorted push_back essentially
			size++;
					
			if (size >= capacity) {
				capacity = capacity * 2;
				unsigned int* newData = new unsigned int[capacity];
				for (int i = 0; i < size - 1; i++) {
					newData[i] = data[i];					
				}
				delete[] data;
				data = newData;
				
		
			}       
			data[size - 1] = value;								// this will put data in the last index
			sort();
			
			
		}
		
		unsigned int& operator[](unsigned int index) {			
			if (index < size)
				return data[index];
			else{						//when an index contains data that should not be read will always return 0
				unsigned int x = 0;
				return x;
			}
		}
		int how_long() {
			return size;
		}
private:

	int size = 0;
	int capacity = 5;
	unsigned int* data;
	
	void inline sort() {								//this function is used to sort the last item in an array
		unsigned int buffer;							//it is essentially the nested portion of the bubble sort algorythm
		for (int i = size - 1; i > 0; i--)				//it's only one item I need to find a place for, the rest of the data is already sorted,
			if (data[i] > data[i - 1]) {				// so it'll be O(n) instead of O(n^2) number of loops.
				buffer = data[i];
				data[i] = data[i - 1];
				data[i - 1] = buffer;
			}
			else										//if index is not bigger that the one above it, we are done
				break;

	}
};


ArrayOfUints myScore;



void SpawnBall(){
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 160 }, 4, "ball");
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
void ResetScene() {
	Play::DestroyGameObjectsByType(1);
	Play::DestroyGameObjectsByType(2);
	SetupScene(7);
	myScore.sort_back(currentscore);
	//myScore.sort();
		
	currentscore = 0;
	SpawnBall();
}

//Step Frame, for each frame we take another step in the simulation
//loop through all the balls, update thier position, then render them
//we pass the paddle in here so we can add it to the collision check for balls
void StepFrame(Paddle& paddle) {
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int objectId : ballIds) {						//works like a python for loop of "for object in vector"
		GameObject& ball = Play::GetGameObject(objectId);  //
		//ball.velocity.y *= 0.7f; //used to test x axis clipping
		//ball.velocity.x *= 0.7f;  //used to test y axis clipping
		Play::DrawDebugText({ DISPLAY_WIDTH - 64, 16 }, std::to_string(ballIds.size()), Play::cGrey, 0);
		Play::UpdateGameObject(ball);
		// if ball hits window edges it will swap across the approprate axis
		if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0)
			ball.velocity.x *= -1;
		if (ball.pos.y > DISPLAY_HEIGHT || IsColliding(paddle, ball))
			ball.velocity.y *= -1;
		if (ball.pos.y < 0){
			if (ballIds.size() == 1){			//if this is the last ball, we reset the scene. This will delete all game objects, and call setupscene, reset our score, etc
				ResetScene();
				//SpawnBall();
				//break;
			}
			Play::DestroyGameObject(objectId);
			break;
		}
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
				currentscore = currentscore + 1;
			}
		}
	
		Play::DrawObject(ball);

		
	}
	
	for (int objectId : brickIds) {
		GameObject& brick  = Play::GetGameObject(objectId);
		Play::DrawObject(brick);
	}
	Play::DrawDebugText({ 64, 16 }, std::to_string(currentscore), Play::cGrey, 0);
	for (int i = 0; i < 5; i++) {

		Play::DrawDebugText({ DISPLAY_WIDTH - 64, 112 - 16 * i }, std::to_string(myScore[i]), Play::cGrey, 0); //added an overload in the playbuffer library, so that it can take std::string and not just char array
	}

}

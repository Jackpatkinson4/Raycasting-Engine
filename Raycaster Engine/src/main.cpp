#include "Game.h"
#include "raylib.h"


int main() 
{
	Game& game = Game::GetInstance();
	game.Run();

	return 0;
}
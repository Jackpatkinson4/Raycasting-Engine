#include "Player.h"
#include "Map.h"
#include "raylib.h"
#include <memory>
#include <vector>

Vector2 initPlayerPosition = { 100, 100 };

std::vector<int> mapArray =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,1,0,1,1,
	1,0,0,0,1,0,0,1,
	1,1,1,1,1,1,1,1,
};

Map map(8, 8, mapArray);

Player player(initPlayerPosition, RED, map);

int main() {
	const int scrWidth = 1280;
	const int scrHeight = 720;

	InitWindow(scrWidth, scrHeight, "Raycaster Engine");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	bool isRunning = true;
	while (isRunning)
	{
		float deltaTime = GetFrameTime();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			isRunning = false;
		}

		player.Update(deltaTime);

		BeginDrawing();
		ClearBackground(DARKGRAY);
#ifdef TOPDOWN
		map.Draw2D();
#endif
		player.Draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
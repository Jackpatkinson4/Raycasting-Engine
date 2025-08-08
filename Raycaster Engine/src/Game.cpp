#include "Player.h"
#include "Map.h"
#include "Game.h"
#include "Renderer.h"
#include "raylib.h"
#include <memory>
#include <vector>

Vector2 initPlayerPosition = { 20, 20 };

std::vector<int> mapArray =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,
	1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,
	1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

Map map(16, 16, mapArray);

Player player(initPlayerPosition, RED, map);

bool topDown = true;

Game::Game(int screenWidth = 1280, int screenHeight = 720, const char* title = "Raycasting Engine") : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_Title(title)
{
}

Game::~Game()
{
	CloseWindow();
}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

void Game::Run()
{
	Init();

	while (!WindowShouldClose())
	{
		Update();
	}

	CloseWindow();
}

void Game::Init()
{
	m_Renderer = new Renderer(m_ScreenWidth, m_ScreenHeight, map);
	InitWindow(m_ScreenWidth, m_ScreenHeight, m_Title);
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
}

void Game::Update()
{
	float deltaTime = GetFrameTime();

	player.Update(deltaTime);
	m_Renderer->UpdateCamera(player.GetPos(), player.GetDir(), player.GetPerp(), player.GetAngle());

	BeginDrawing();
	ClearBackground(DARKGRAY);

	if (topDown)
	{
		m_Renderer->Draw();
		map.Draw2D();
		player.Draw2D();
	}
	else
	{
		m_Renderer->Draw();
	}

	EndDrawing();
}

#pragma once
#include "Renderer.h"

class Game {
public:

	static Game& GetInstance();
	void Run();

private:
	int m_ScreenWidth, m_ScreenHeight;
	const char* m_Title;
	Renderer* m_Renderer;

	Game(int screenWidth, int screenHeight, const char* title);
	~Game();

	void Init();
	void Update();
};
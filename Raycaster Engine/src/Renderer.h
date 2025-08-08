#pragma once
#include "Map.h"
#include "raylib.h"
#include "raymath.h"
#include <memory>
#include <vector>

struct RendererCamera
{
	Vector2 cameraPos, cameraDir, cameraPerp;
	float cameraAngle;
};

struct Stripe
{
	Vector2 start;
	Vector2 end;
	Color color;
};

class Renderer
{
public:
	Renderer(int screenWidth, int screenHeight, Map map);

	void SetMap(Map map);

	void Draw();

	void UpdateCamera(Vector2 newPos, Vector2 newDir, Vector2 newPerp, float newAngle);

private:
	int m_ScreenWidth, m_ScreenHeight;
	RendererCamera m_Camera;
	Map m_Map;
	std::vector<Stripe> m_Stripes;

	void CastRays();
};

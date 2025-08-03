#pragma once
#include "Map.h"
#include "raylib.h"
#include "raymath.h"

struct PlayerRay
{
	Vector2 rayDirection;
	Vector2 rayHitPos;
	double rayDistance;
	int side;
};

inline PlayerRay createRay(Vector2 rayDir, Vector2 rayPos, double rayDist, int side)
{
	PlayerRay ray;
	ray.rayDirection = rayDir;
	ray.rayHitPos = rayPos;
	ray.rayDistance = rayDist;
	ray.side = side;
	return ray;
}

class Player {
public:
	Player(Vector2 pos, Color color, Map map);

	void Draw();
	void Update(float delta);
	Vector2 DetectCollisions(Vector2 pos, Vector2 step, Map map);
	PlayerRay CastRay(Vector2 pos, Vector2 dir);

	Vector2 GetPos() const { return m_Pos; }
	float GetAngle() const { return m_Angle; }
private:
	Vector2 m_Pos, m_Direction, m_Perpendicular;
	float m_Angle;
	Color m_Color;
	Map m_Map;
};
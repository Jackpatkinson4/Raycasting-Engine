#include "Player.h"
#include "Map.h"
#include "Utils.h"
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <iostream>

#define MOVEMENT_SPEED 3;

Player::Player(Vector2 pos, Color color, Map map) : m_Pos(pos), m_Color(color), m_Map(map)
{
	m_Angle = 0;
	m_Direction = { 1, 0 };
	m_Perpendicular = { 0, 0.66 };
}

void Player::Draw()
{

#ifdef TOPDOWN
	float fov = 1.57079632679;
	float projectionDistance = 0.5f * m_Map.GetCellSize() / tan(0.5 * 1.57079632679);
	float rayAngle = m_Angle - fov + 0.785398;

	DrawRectangleV(m_Pos, { 8,8 }, m_Color);
	DrawLineEx(Vector2AddValue(m_Pos, 4), Vector2AddValue(m_Pos, 4) + m_Direction * 25, 4, m_Color);

	for (int i = 0; i < 1280; i++)
	{
		PlayerRay currRay = CastRay(m_Pos, { cos(rayAngle),sin(rayAngle) });
		DrawLineEx(Vector2AddValue(m_Pos, 4), Vector2AddValue(currRay.rayHitPos, 4), 2, GREEN);
		rayAngle += fov / 1280;
	}

#else
	for (int i = 0; i < 1280; i++)
	{
		float cameraX = 2 * (i / 1280.0) - 1;
		Vector2 rayDirection = m_Direction + m_Perpendicular * cameraX;
		PlayerRay currRay = CastRay(m_Pos, rayDirection);
		
		float angleOffset = Vector2Angle(rayDirection, m_Direction);
		float lineHeight = 720 / (currRay.rayDistance * cos(angleOffset));
		lineHeight *= m_Map.GetCellSize();
		Vector2 lineStart = { i, (720-lineHeight)/2};
		if (lineStart.y < 0) lineStart.y = 0;
		Vector2 lineEnd = { i, (lineHeight+720)/2 };
		if (lineEnd.y >= 720) lineEnd.y = 720;

		Color wallColor = { 0, 255 * (1 - currRay.rayDistance / 720), 0, 255 };
		if (currRay.side == 1) 
		{
			wallColor.g = 127 * (1 - currRay.rayDistance / 720);
		}
		
		DrawLineEx(lineStart, lineEnd, 1, wallColor);
	}
#endif
}

void Player::Update(float delta)
{
	Vector2 step = { 0.0f, 0.0f };

	if (IsKeyDown(KEY_LEFT))
	{
		m_Angle -= 0.1;
		if (m_Angle < 0)
		{
			m_Angle += 2 * PI;
		}
		m_Direction = { cos(m_Angle), sin(m_Angle) };
		m_Perpendicular = { cos(m_Angle + (float)PI / 2), sin(m_Angle + (float)PI / 2) };
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		m_Angle += 0.1;
		if (m_Angle > 2 * PI)
		{
			m_Angle -= 2 * PI;
		}
		m_Direction = { cos(m_Angle), sin(m_Angle) };
		m_Perpendicular = { cos(m_Angle + (float)PI / 2), sin(m_Angle + (float)PI / 2) };
	}

	if (IsKeyDown(KEY_A))
	{
		step -= m_Perpendicular * MOVEMENT_SPEED;
	}
	else if (IsKeyDown(KEY_D))
	{
		step += m_Perpendicular * MOVEMENT_SPEED;
	}

	if (IsKeyDown(KEY_W))
	{
		step += m_Direction * MOVEMENT_SPEED;
	}
	else if (IsKeyDown(KEY_S))
	{
		step -= m_Direction * MOVEMENT_SPEED;
	}

	m_Pos = DetectCollisions(m_Pos, step, m_Map);
}

Vector2 Player::DetectCollisions(Vector2 pos, Vector2 step, Map map)
{
	if (Utils::MapCollision(pos + step, map) == 0)
	{
		pos += step;
	}
	else if (Utils::MapCollision(pos.x + step.x, pos.y, map) == 0)
	{
		Vector2 nextPos = { pos.x + step.x, pos.y };
		pos = nextPos;
	}
	else if (Utils::MapCollision(pos.x, pos.y + step.y, map) == 0)
	{
		Vector2 nextPos = { pos.x, pos.y + step.y };
		pos = nextPos;
	}

	return pos;
}

PlayerRay Player::CastRay(Vector2 pos, Vector2 dir)
{
	// Ray casting logic
	bool hit = 0;
	int side = 0; // 0 if x distance is shorter, 1 if y distance is shorter

	int stepX = 0, stepY = 0;
	Vector2 rayDirection = dir;
	int cellSize = m_Map.GetCellSize();

	double rayDist, sideDistX, sideDistY;
	double deltaDistX, deltaDistY;

	rayDist = 0;
	sideDistX = 0;
	sideDistY = 0;

	deltaDistX = sqrt(1 + pow(rayDirection.y / rayDirection.x, 2)) * cellSize;
	deltaDistY = sqrt(1 + pow(rayDirection.x / rayDirection.y, 2)) * cellSize;

	Vector2 cellPos = { floor(pos.x / cellSize),floor(pos.y / cellSize) };

	if (rayDirection.x < 0)
	{
		stepX = -1;
		sideDistX = (pos.x / cellSize - cellPos.x) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = ((cellPos.x + 1) - pos.x / cellSize) * deltaDistX;
	}
	if (rayDirection.y < 0)
	{
		stepY = -1;
		sideDistY = (pos.y / cellSize - cellPos.y) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = ((cellPos.y + 1) - pos.y / cellSize) * deltaDistY;
	}

	while (hit == 0)
	{

		if (sideDistX < sideDistY)
		{
			rayDist = sideDistX;
			sideDistX += deltaDistX;
			cellPos.x += stepX;
			side = 0;
		}
		else
		{
			rayDist = sideDistY;
			sideDistY += deltaDistY;
			cellPos.y += stepY;
			side = 1;
		}

		if (m_Map.GetValueAtCoord(cellPos) > 0)
		{
			hit = 1; // We hit a wall
		}

		if (0 > cellPos.x || 0 > cellPos.y || m_Map.GetMapX() <= cellPos.x && m_Map.GetMapY() <= cellPos.y)
		{
			hit = 1; // Hit border
		}
	}

	Vector2 rayHitPos = pos + rayDirection * rayDist;
	
	PlayerRay returnRay = createRay(rayDirection, rayHitPos, rayDist, side);

	return returnRay;
}

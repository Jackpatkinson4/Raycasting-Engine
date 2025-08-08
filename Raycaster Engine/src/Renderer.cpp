#include "Renderer.h"
#include "Map.h"
#include "Player.h"
#include <memory>
#include <vector>

Renderer::Renderer(int screenWidth, int screenHeight, Map map)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
	m_Camera = {};
	m_Map = map;
}

void Renderer::SetMap(Map map)
{
	m_Map = map;
}

void Renderer::Draw()
{
	CastRays();
	for (int i = 0; i < m_ScreenWidth; i++)
	{
		Stripe currStripe = m_Stripes[i];
		DrawLineEx(currStripe.start, currStripe.end, 1, currStripe.color);
	}
}

void Renderer::UpdateCamera(Vector2 newPos, Vector2 newDir, Vector2 newPerp, float newAngle)
{
	m_Camera.cameraPos = newPos;
	m_Camera.cameraDir = newDir;
	m_Camera.cameraPerp = newPerp;
	m_Camera.cameraAngle = newAngle;
}

void Renderer::CastRays()
{
	if (m_Stripes.size() != 0)
	{
		m_Stripes.clear();
	}

	for (int i = 0; i < m_ScreenWidth; i++)
	{
		float cameraX = 2 * (i / static_cast<float>(m_ScreenWidth)) - 1;
		Vector2 rayDirection = m_Camera.cameraDir + m_Camera.cameraPerp * cameraX;
		PlayerRay currRay = Player::CastRay(m_Camera.cameraPos, rayDirection, m_Map);

		float angleOffset = Vector2Angle(rayDirection, m_Camera.cameraDir);
		float lineHeight = m_ScreenHeight / (currRay.rayDistance * cos(angleOffset));
		lineHeight *= m_Map.GetCellSize();
		Vector2 lineStart = { i, (m_ScreenHeight - lineHeight) / 2 };
		if (lineStart.y < 0) lineStart.y = 0;
		Vector2 lineEnd = { i, (lineHeight + m_ScreenHeight) / 2 };
		if (lineEnd.y >= m_ScreenHeight) lineEnd.y = m_ScreenHeight;

		Color wallColor = { 0, 255 * (1 - currRay.rayDistance / m_ScreenHeight), 0, 255 };
		if (currRay.side == 1)
		{
			wallColor.g = 127 * (1 - currRay.rayDistance / m_ScreenHeight);
		}

		Stripe newStripe = { lineStart, lineEnd, wallColor };
		m_Stripes.push_back(newStripe);
	}
}

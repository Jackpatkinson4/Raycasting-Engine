#include "Map.h"
#include "raylib.h"
#include <memory>
#include <iostream>
#include <vector>

Map::Map(int x, int y, std::vector<int> mapArr) : m_MapX(x), m_MapY(y), m_MapArr(mapArr)
{
}

void Map::Draw2D()
{
	int xOffset, yOffset;
	Vector2 boxPos, boxSize;
	Color boxColor;
	for (int y = 0; y < m_MapY; y++)
	{
		for (int x = 0; x < m_MapX; x++)
		{
			int index = y * m_MapX + x;
			if (m_MapArr[index] == 1)
			{
				boxColor = WHITE;
			}
			else
			{
				boxColor = BLACK;
			}
			xOffset = x * m_CellSize;
			yOffset = y * m_CellSize;
			boxPos = { (float)xOffset,(float)yOffset};
			boxSize = { (float)m_CellSize - 1, (float)m_CellSize - 1 };
			DrawRectangleV(boxPos,boxSize,boxColor);
		}
	}
}

int Map::GetValueAtIndex(int index)
{
	if (index < 0 || index > m_MapX * m_MapY)
	{
		return 0;
	}
	return m_MapArr[index];
}

int Map::GetValueAtCoord(int x, int y)
{
	int index = y * m_MapX + x;
	return GetValueAtIndex(index);
}

int Map::GetValueAtCoord(Vector2 pos)
{
	int index = pos.y * m_MapX + pos.x;
	return GetValueAtIndex(index);
}

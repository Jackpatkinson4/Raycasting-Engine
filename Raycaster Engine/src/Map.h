#pragma once
#include "raylib.h"
#include <memory>
#include <vector>

#define TOPDOWN
#undef TOPDOWN

class Map
{
public:
	Map(int x, int y, std::vector<int> mapArr);

	void Draw2D();

	int GetMapX() const { return m_MapX; }
	int GetMapY() const { return m_MapY; }
	int GetCellSize() const { return m_CellSize; }

	int GetValueAtIndex(int index);
	int GetValueAtCoord(int x, int y);
	int GetValueAtCoord(Vector2 pos);
private:
	int m_MapX, m_MapY;
	int m_CellSize = 64;
	std::vector<int> m_MapArr;
};


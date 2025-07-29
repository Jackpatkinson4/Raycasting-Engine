#pragma once

#include "Map.h"
#include "raylib.h"
#include <vector>

namespace Utils {
	bool MapCollision(int x, int y, Map map);
	bool MapCollision(Vector2 pos, Map map);
}


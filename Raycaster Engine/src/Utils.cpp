#include "Utils.h"
#include "raylib.h"

bool Utils::MapCollision(int x, int y, Map map)
{
    float cellX = x / map.GetCellSize();
    float cellY = y / map.GetCellSize();

    for (int i = 0; i < 4; i++)
    {
        int x = 0;
        int y = 0;

        switch (i)
        {
            case 0:
            {
                x = floor(cellX);
                y = floor(cellY);
                break;
            }
            case 1:
            {
                x = ceil(cellX);
                y = floor(cellY);
                break;
            }
            case 2:
            {
                x = floor(cellX);
                x = ceil(cellY);
                break;
            }
            case 3:
            {
                x = ceil(cellX);
                x = ceil(cellY);
                break;
            }    
        }

        if (map.GetValueAtCoord(x,y) == 1)
        {
            return 1;
        }

        return 0;
    }
}

bool Utils::MapCollision(Vector2 pos, Map map)
{
    float cellX = pos.x / map.GetCellSize();
    float cellY = pos.y / map.GetCellSize();

    for (int i = 0; i < 4; i++)
    {
        int x = 0;
        int y = 0;

        switch (i)
        {
            case 0:
            {
                x = floor(cellX);
                y = floor(cellY);
                break;
            }
            case 1:
            {
                x = ceil(cellX);
                y = floor(cellY);
                break;
            }
            case 2:
            {
                x = floor(cellX);
                x = ceil(cellY);
                break;
            }
            case 3:
            {
                x = ceil(cellX);
                x = ceil(cellY);
                break;
            }
        }

        if (map.GetValueAtCoord(x,y) == 1)
        {
            return 1;
        }

        return 0;
    }
}

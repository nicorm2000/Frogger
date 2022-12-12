#pragma once

#include "raylib.h"

namespace game
{
	struct EndCells
	{
		Vector2 endCellsPosition{};
		Vector2 endCellsSize;
		Color endCellsColor;
	};

	EndCells CreateEndCells(EndCells& endCells, float posX, float width);

	void DrawEndCells(EndCells endCells);
}
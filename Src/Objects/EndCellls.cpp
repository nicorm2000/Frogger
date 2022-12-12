#include "Objects/EndCellls.h"

namespace game
{
	EndCells CreateEndCells(EndCells& endCells, float posX, float width)
	{
		endCells.endCellsPosition.x = posX;
		endCells.endCellsPosition.y = 64;
		endCells.endCellsSize.x = width;
		endCells.endCellsSize.y = 64;
		endCells.endCellsColor = BLANK;

		return endCells;
	}

	//Only used to check the collision zone
	void DrawEndCells(EndCells endCells)
	{
		DrawRectangle(static_cast<int>(endCells.endCellsPosition.x), static_cast<int>(endCells.endCellsPosition.y), static_cast<int>(endCells.endCellsSize.x), static_cast<int>(endCells.endCellsSize.y), endCells.endCellsColor);
	}
}
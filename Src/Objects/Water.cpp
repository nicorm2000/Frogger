#include "Objects/Water.h"

#include "raylib.h"

namespace game
{
	Water CreateWater(Water& water)
	{
		water.waterPosition.x = 0;
		water.waterPosition.y = 64;
		water.waterSize.x = 1024;
		water.waterSize.y = 384;
		water.waterColor = BLANK;

		return water;
	}

	//Only used to check the collision zone
	void DrawWater(Water water)
	{
		DrawRectangle(static_cast<int>(water.waterPosition.x), static_cast<int>(water.waterPosition.y), static_cast<int>(water.waterSize.x), static_cast<int>(water.waterSize.y), water.waterColor);
	}
}
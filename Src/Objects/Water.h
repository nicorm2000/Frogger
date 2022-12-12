#pragma once

#include "raylib.h"

namespace game
{
	struct Water
	{
		Vector2 waterPosition{};
		Vector2 waterSize;
		bool isOnWater;
		Color waterColor;
	};

	Water CreateWater(Water& water);

	void DrawWater(Water water);
}
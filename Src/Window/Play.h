#pragma once

#include "Objects/Log.h"
#include "Objects/LandEnemy.h"

namespace game
{
	const int LOG_COUNT = SMALL_LOG_COUNT + MEDIUM_LOG_COUNT + BIG_LOG_COUNT + SMALL_LOG_COUNT2 + MEDIUM_LOG_COUNT2 + BIG_LOG_COUNT2;

	const int LAND_ENEMIES_COUNT = MOTORCYCLE_COUNT + CAR_COUNT + FAST_CAR_COUNT + VAN_COUNT + BUS_COUNT + TRUCK_COUNT;

	void DrawMap();

	void DrawExitWindow();
}
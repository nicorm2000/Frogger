#pragma once

#include "Objects/Log.h"
#include "Objects/LandEnemy.h"

namespace game
{
	const int CELL_SIZE = 64;

	const int SPACE_BETWEEN_FLIES = 192;

	const int FLIES_COUNT = 5;

	const int FIRST_FLY_POS_X = 106;

	const int LOG_COUNT = SMALL_LOG_COUNT + MEDIUM_LOG_COUNT + BIG_LOG_COUNT + SMALL_LOG_COUNT2 + MEDIUM_LOG_COUNT2 + BIG_LOG_COUNT2;

	const int LAND_ENEMIES_COUNT = MOTORCYCLE_COUNT + CAR_COUNT + FAST_CAR_COUNT + VAN_COUNT + BUS_COUNT + TRUCK_COUNT;

	const int LAND_ENEMIES_DISTANCE = 500;

	const int LOG_DISTANCE = 500;

	const int LEFT_BUTTON_POSITION_X = 350;

	const int RIGHT_BUTTON_POSITION_X = 530;
	
	const int BUTTON_POSITION_Y = 525;

	const int BUTTON_SIZE_X = 150;

	const int BUTTON_SIZE_Y = 100;

	const int FROG_LIVES = 5;

	const float FROG_INITIAL_POSITION_X = 486.0F;
	
	const float FROG_INITIAL_POSITION_Y = 967.5f;

	const float TIMER = 30.0f;

	void DrawMap(Texture2D bg);

	void DrawExitWindow(Font gameFont);

	void DrawWinMenu(Font gameFont);

	void DrawLoseMenu(Font gameFont);

	void ResetGame();
}
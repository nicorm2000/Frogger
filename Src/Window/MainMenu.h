#pragma once

#include "raylib.h"

namespace game
{
	const int EXIT_BUTTON_POSITION_X = 10;

	const int EXIT_BUTTON_POSITION_Y = 10;

	const int EXIT_BUTTON_SIZE_X = 45;

	const int EXIT_BUTTON_SIZE_Y = 45;

	enum class GameState
	{
		GAMETITLE = 0,
		GAME,
		HOWTOPLAY,
		CREDITS,
		EXIT
	};

	void Game();

	void MainMenuLoad();

	void MainMenuLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick);

	void MainMenuDraw(Texture mainMenuScene);

	void UnloadDataMainMenu(Sound frogRibbitClick, Texture mainMenuScene);
}
#pragma once

#include "raylib.h"

namespace game
{
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

	void MainMenuDraw();

	void UnloadDataMainMenu(Sound frogRibbitClick);
}
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

	void MainMenuLogic(Vector2 mousePosition, GameState& gameState);

	void MainMenuDraw();
}
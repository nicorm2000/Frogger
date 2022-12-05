#pragma once

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

	void GameLoop();
}
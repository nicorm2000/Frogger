#pragma once
#include "Window/HowToPlay.h"

#include "raylib.h"

namespace game
{
	void HowToPlayLogic(Vector2 mousePosition, GameState& gameState);

	void HowToPlayDraw();
}
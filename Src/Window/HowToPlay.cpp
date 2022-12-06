#include "Window/MainMenu.h"
#include "Window/HowToPlay.h"

#include "raylib.h"

namespace game
{
	void HowToPlayLogic(Vector2 mousePosition, GameState& gameState)
	{
		if (CheckCollisionPointRec(mousePosition, { 10, 10, 45, 45 }))
		{
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				gameState = GameState::GAMETITLE;
			}
		}
	}

	void HowToPlayDraw()
	{
		DrawRectangle(10, 10, 45, 45, RED);
		DrawText("x", 20, 5, 50, WHITE);
	}
}
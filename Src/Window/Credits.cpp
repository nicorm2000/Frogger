#include "Window/MainMenu.h"
#include "Window/Credits.h"

#include "raylib.h"

namespace game
{
	void CreditsLogic(Vector2 mousePosition, GameState& gameState)
	{
		if (CheckCollisionPointRec(mousePosition, { static_cast<float>(GetScreenWidth() / 2) - 87.5f, static_cast<float>(GetScreenHeight() / 2) - 20, 190, 85 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				OpenURL("https://nicorm.itch.io/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 10, 10, 45, 45 }))
		{
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				gameState = GameState::GAMETITLE;
			}
		}
	}

	void CreditsDraw()
	{
		DrawRectangle(10, 10, 45, 45, RED);
		DrawText("x", 20, 5, 50, WHITE);

		DrawRectangle(static_cast<int>(GetScreenWidth() / 2) - 0 - 87, static_cast<int>(GetScreenHeight() / 2) - 20, 190, 85, BLACK);
		DrawRectangle(static_cast<int>(GetScreenWidth() / 2) - 0 - 82, static_cast<int>(GetScreenHeight() / 2) - 15, 180, 75, RED);
		DrawText("Itch.io", static_cast<int>(GetScreenWidth() / 2) - MeasureText("Itch.io", 25), static_cast<int>(GetScreenHeight() / 2), 50, BLACK);
		DrawRectangle(250, GetScreenHeight() / 2 - 115, 550, 85, BLACK);
		DrawRectangle(255, GetScreenHeight() / 2 - 110, 540, 75, WHITE);
		DrawText("Nicolas Ramos Marin", static_cast<int>(GetScreenWidth() / 2) - MeasureText("Nicolas Ramos Marin", 25), static_cast<int>(GetScreenHeight() / 2) - 100, 50, BLACK);
	}
}
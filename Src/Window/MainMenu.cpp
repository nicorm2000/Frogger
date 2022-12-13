#include "Window/MainMenu.h"
#include "Window/Play.h"

#include "raylib.h"

namespace game
{
	void MainMenuLoad()
	{
		Sound frogRibbitClick = LoadSound("Resources/Sounds/Frog-sound-ribbit.wav");
	}

	void MainMenuLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick)
	{
		if (CheckCollisionPointRec(mousePosition, { static_cast<float>(GetScreenWidth() / 2) - 150 / 2, 200, 150, 50 }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				ResetGame();

				gameState = GameState::GAME;
			}
		}

		if (CheckCollisionPointRec(mousePosition, { static_cast<float>(GetScreenWidth() / 2) - (375 / 2) + 5, 275, 375, 50 }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::HOWTOPLAY;
			}
		}

		if (CheckCollisionPointRec(mousePosition, { static_cast<float>(GetScreenWidth() / 2) - (250 / 2), 350, 250, 50 }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::CREDITS;
			}
		}

		if (CheckCollisionPointRec(mousePosition, { static_cast<float>(GetScreenWidth() / 2) - (150 / 2), 425, 150, 150 }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				gameState = GameState::EXIT;
			}
		}
	}

	void MainMenuDraw()
	{
		DrawRectangle(GetScreenWidth() / 2 - (150 / 2), 197, 150, 50, BLACK);
		DrawText("PLAY", GetScreenWidth() / 2 - 50 - 15, 200, 50, WHITE);

		DrawRectangle(GetScreenWidth() / 2 - (375 / 2) + 5, 272, 375, 50, BLACK);
		DrawText("HOW TO PLAY", GetScreenWidth() / 2 - 50 - 125, 275, 50, WHITE);

		DrawRectangle(GetScreenWidth() / 2 - (250 / 2), 347, 250, 50, BLACK);
		DrawText("CREDITS", GetScreenWidth() / 2 - 50 - 65, 350, 50, WHITE);

		DrawRectangle(GetScreenWidth() / 2 - (150 / 2), 422, 150, 50, BLACK);
		DrawText("EXIT", GetScreenWidth() / 2 - 50 - 10, 425, 50, WHITE);
	}

	void UnloadDataMainMenu(Sound frogRibbitClick)
	{
		UnloadSound(frogRibbitClick);
	}
}
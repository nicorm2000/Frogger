#include "Window/MainMenu.h"
#include "Window/Credits.h"

#include "raylib.h"

namespace game
{
	void CreditsLoad()
	{
		Sound frogRibbitClick = LoadSound("Resources/Sounds/Frog-sound-ribbit.wav");

		Texture creditsScene = LoadTexture("Resources/Textures/creditsScene.png");
	}

	void CreditsLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick)
	{
		if (CheckCollisionPointRec(mousePosition, { static_cast<float>(GetScreenWidth() / 2) - 87.5f, static_cast<float>(GetScreenHeight() / 2) - 20, 190, 85 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://nicorm.itch.io/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 10, 10, 45, 45 }))
		{
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::GAMETITLE;
			}
		}
	}

	void CreditsDraw(Texture creditsScene)
	{
		DrawTexture(creditsScene, 0, 0, WHITE);

		DrawRectangle(10, 10, 45, 45, RED);
		DrawText("x", 20, 5, 50, WHITE);
	}

	void UnloadDataCredits(Sound frogRibbitClick, Texture creditsScene)
	{
		UnloadSound(frogRibbitClick);

		UnloadTexture(creditsScene);
	}
}
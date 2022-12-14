#include "Window/MainMenu.h"
#include "Window/HowToPlay.h"

#include "raylib.h"

namespace game
{
	void HowToPlayLoad()
	{
		Sound frogRibbitClick = LoadSound("Resources/Sounds/Frog-sound-ribbit.wav");
	}

	void HowToPlayLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick)
	{
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

	void HowToPlayDraw()
	{
		DrawRectangle(10, 10, 45, 45, RED);
		DrawText("x", 20, 5, 50, WHITE);
	}

	void UnloadDataHowToPlay(Sound frogRibbitClick)
	{
		UnloadSound(frogRibbitClick);
	}
}
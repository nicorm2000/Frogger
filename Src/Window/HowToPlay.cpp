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
		int xPosX = 20;
		int xPosY = 5;
		int xFontSize = 50;

		DrawRectangle(EXIT_BUTTON_POSITION_X, EXIT_BUTTON_POSITION_Y, EXIT_BUTTON_SIZE_X, EXIT_BUTTON_SIZE_Y, RED);
		DrawText("x", xPosX, xPosY, xFontSize, WHITE);
	}

	void UnloadDataHowToPlay(Sound frogRibbitClick)
	{
		UnloadSound(frogRibbitClick);
	}
}
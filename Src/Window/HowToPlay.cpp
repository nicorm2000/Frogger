#include "Window/MainMenu.h"
#include "Window/HowToPlay.h"

#include "raylib.h"

namespace game
{
	void HowToPlayLoad()
	{
		Sound frogRibbitClick = LoadSound("Resources/Sounds/Frog-sound-ribbit.wav");

		Texture howToPlayScene = LoadTexture("Resources/Textures/howToPlayScene.png");
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

	void HowToPlayDraw(Texture howToPlayScene)
	{
		int xPosX = 20;
		int xPosY = 5;
		int xFontSize = 50;

		DrawTexture(howToPlayScene, 0, 0, WHITE);

		DrawRectangle(EXIT_BUTTON_POSITION_X, EXIT_BUTTON_POSITION_Y, EXIT_BUTTON_SIZE_X, EXIT_BUTTON_SIZE_Y, RED);
		DrawText("x", xPosX, xPosY, xFontSize, WHITE);
	}

	void UnloadDataHowToPlay(Texture howToPlayScene)
	{
		UnloadTexture(howToPlayScene);
	}
}
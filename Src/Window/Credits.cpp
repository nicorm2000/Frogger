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
		if (CheckCollisionPointRec(mousePosition, { 180, 140, 660, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://nicorm.itch.io/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 490, 280, 310, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://www.dafont.com/es/abalone-smile.font");
				OpenURL("https://www.dafont.com/es/khurasan.d5849");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 500, 415, 315, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://www.dargolan-free.com/video-game-music");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 200, 645, 630, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://freesound.org/people/SoundDesignForYou/sounds/646671/");
				OpenURL("https://freesound.org/people/SoundDesignForYou/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 50, 735, 370, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://orangefreesounds.com/frog-sound-ribbit/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 650, 735, 280, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://www.zapsplat.com/music/cartoon-spring-boing-jump-2/");
				OpenURL("https://www.zapsplat.com/author/zapsplat/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 90, 810, 360, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://freesound.org/people/MATRIXXX_/sounds/657930/");
				OpenURL("https://freesound.org/people/MATRIXXX_/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { 570, 810, 430, 70 }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://freesound.org/people/Whiprealgood/sounds/87535/");
				OpenURL("https://freesound.org/people/Whiprealgood/");
			}
		}

		if (CheckCollisionPointRec(mousePosition, { EXIT_BUTTON_POSITION_X, EXIT_BUTTON_POSITION_Y, EXIT_BUTTON_SIZE_X, EXIT_BUTTON_SIZE_Y }))
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
		int xPosX = 20;
		int xPosY = 5;
		int xFontSize = 50;

		DrawTexture(creditsScene, 0, 0, WHITE);

		DrawRectangle(EXIT_BUTTON_POSITION_X, EXIT_BUTTON_POSITION_Y, EXIT_BUTTON_SIZE_X, EXIT_BUTTON_SIZE_Y, RED);
		DrawText("x", xPosX, xPosY, xFontSize, WHITE);
	}

	void UnloadDataCredits(Sound frogRibbitClick, Texture creditsScene)
	{
		UnloadSound(frogRibbitClick);

		UnloadTexture(creditsScene);
	}
}
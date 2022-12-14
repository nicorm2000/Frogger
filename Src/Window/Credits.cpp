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
		float nicormPosX = 180;
		float nicormPosY = 140;
		float nicormSizeX = 660;

		if (CheckCollisionPointRec(mousePosition, { nicormPosX, nicormPosY, nicormSizeX, CREDITS_BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://nicorm.itch.io/");
			}
		}

		float fontPosX = 490;
		float fontPosY = 280;
		float fontSizeX = 310;

		if (CheckCollisionPointRec(mousePosition, { fontPosX, fontPosY, fontSizeX, CREDITS_BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://www.dafont.com/es/abalone-smile.font");
				OpenURL("https://www.dafont.com/es/khurasan.d5849");
			}
		}

		float bgMusicPosX = 500;
		float bgMusicPosY = 415;
		float bgMusicSizeX = 315;

		if (CheckCollisionPointRec(mousePosition, { bgMusicPosX, bgMusicPosY, bgMusicSizeX, CREDITS_BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://www.dargolan-free.com/video-game-music");
			}
		}

		float pickUpFlyPosX = 200;
		float pickUpFlyPosY = 645;
		float pickUpFlySizeX = 630;

		if (CheckCollisionPointRec(mousePosition, { pickUpFlyPosX, pickUpFlyPosY, pickUpFlySizeX, CREDITS_BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://freesound.org/people/SoundDesignForYou/sounds/646671/");
				OpenURL("https://freesound.org/people/SoundDesignForYou/");
			}
		}

		float ribbitPosX = 50;
		float ribbitPosY = 735;
		float ribbitSizeX = 370;

		if (CheckCollisionPointRec(mousePosition, { ribbitPosX, ribbitPosY, ribbitSizeX, CREDITS_BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://orangefreesounds.com/frog-sound-ribbit/");
			}
		}

		float jumpPosX = 650;
		float jumpPosY = 735;
		float jumpSizeX = 280;

		if (CheckCollisionPointRec(mousePosition, { jumpPosX, jumpPosY, jumpSizeX, CREDITS_BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://www.zapsplat.com/music/cartoon-spring-boing-jump-2/");
				OpenURL("https://www.zapsplat.com/author/zapsplat/");
			}
		}

		float drownPosX = 90;
		float drownPosY = 810;
		float drownSizeX = 360;

		if (CheckCollisionPointRec(mousePosition, { drownPosX, drownPosY, drownSizeX, CREDITS_BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				OpenURL("https://freesound.org/people/MATRIXXX_/sounds/657930/");
				OpenURL("https://freesound.org/people/MATRIXXX_/");
			}
		}

		float splatPosX = 570;
		float splatPosY = 810;
		float splatSizeX = 430;

		if (CheckCollisionPointRec(mousePosition, { splatPosX, splatPosY, splatSizeX, CREDITS_BUTTON_SIZE_Y }))
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

	void UnloadDataCredits(Texture creditsScene)
	{
		UnloadTexture(creditsScene);
	}
}
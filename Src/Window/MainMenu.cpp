#include "Window/MainMenu.h"
#include "Window/Play.h"

#include "raylib.h"

namespace game
{
	void MainMenuLoad()
	{
		Sound frogRibbitClick = LoadSound("Resources/Sounds/Frog-sound-ribbit.wav");

		Texture mainMenuScene = LoadTexture("Resources/Textures/mainMenuScene.png");
	}

	void MainMenuLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick)
	{
		float gamePosX = 370;
		float gamePosY = 455;
		float gameSizeX = 280;
		float gameSizeY = 150;

		if (CheckCollisionPointRec(mousePosition, { gamePosX, gamePosY, gameSizeX, gameSizeY }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				ResetGame();

				gameState = GameState::GAME;
			}
		}

		float howToPlayPosX = 750;
		float howToPlayPosY = 330;
		float howToPlaySizeX = 260;
		float howToPlaySizeY = 190;

		if (CheckCollisionPointRec(mousePosition, { howToPlayPosX, howToPlayPosY, howToPlaySizeX, howToPlaySizeY }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::HOWTOPLAY;
			}
		}

		float creditsPosX = 10;
		float creditsPosY = 385;
		float creditsSizeX = 280;
		float creditsSizeY = 80;

		if (CheckCollisionPointRec(mousePosition, { creditsPosX, creditsPosY, creditsSizeX, creditsSizeY }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::CREDITS;
			}
		}

		float exitPosX = 440;
		float exitPosY = 930;
		float exitSizeX = 150;
		float exitSizeY = 80;

		if (CheckCollisionPointRec(mousePosition, { exitPosX, exitPosY, exitSizeX, exitSizeY }))
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				gameState = GameState::EXIT;
			}
		}
	}

	void MainMenuDraw(Texture mainMenuScene)
	{
		DrawTexture(mainMenuScene, 0, 0, WHITE);
	}

	void UnloadDataMainMenu(Texture mainMenuScene)
	{
		UnloadTexture(mainMenuScene);
	}
}
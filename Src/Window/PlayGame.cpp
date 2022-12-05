#include "Window/PlayGame.h"
#include "Objects/Frog.h"

#include "raylib.h"

namespace game
{

	static void Initialize();

	static void Close();

	void CheckPlayerInput(Frog& frog, bool& playingGame);

	void GameLoop()
	{
		Initialize();
		HideCursor();
		SetExitKey(KEY_NULL);

		bool playingGame = true;

		Frog frog;

		CreateFrog(frog);

		while (playingGame && !WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(BLACK);

			//Logic

			CheckPlayerInput(frog, playingGame);

			//Draw

			DrawRectangle(510, 0, 2, 1024, WHITE);

			if (frog.isAlive)
			{
				DrawFrog(frog);
			}

			EndDrawing();
		}

		Close();
	}

	static void Initialize()
	{
		InitWindow(1024, 1024, "Frogger 0.1");
	}

	static void Close()
	{
		CloseWindow();
	}

	void CheckPlayerInput(Frog& frog, bool& playingGame)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			playingGame = false;
		}

		if (IsKeyPressed(KEY_UP))
		{
			if (frog.frogPosition.y >= 64)
			{
				frog.frogPosition.y -= 64;
			}
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			if (frog.frogPosition.y <= 959)
			{
				frog.frogPosition.y += 64;
			}
		}

		if (IsKeyPressed(KEY_RIGHT))
		{
			if (frog.frogPosition.x <= 933)
			{
				frog.frogPosition.x += 64;
			}
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			if (frog.frogPosition.x >= 39)
			{
				frog.frogPosition.x -= 64;
			}
		}
	}

}
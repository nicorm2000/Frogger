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
		//HideCursor();
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
			
			//Map
			{
				DrawRectangle(0, 0, 1024, 64, DARKGRAY);

				//Objective zone
				DrawRectangle(95, 0, 64, 64, LIME);
				DrawRectangle(287, 0, 64, 64, LIME);
				DrawRectangle(479, 0, 64, 64, LIME);
				DrawRectangle(671, 0, 64, 64, LIME);
				DrawRectangle(863, 0, 64, 64, LIME);

				//Water
				DrawRectangle(0, 64, 1024, 64, SKYBLUE);
				DrawRectangle(0, 128, 1024, 64, SKYBLUE);
				DrawRectangle(0, 192, 1024, 64, SKYBLUE);
				DrawRectangle(0, 256, 1024, 64, SKYBLUE);
				DrawRectangle(0, 320, 1024, 64, SKYBLUE);
				DrawRectangle(0, 384, 1024, 64, SKYBLUE);

				//Sidewalk
				DrawRectangle(0, 448, 1024, 64, LIGHTGRAY);

				//Street
				DrawRectangle(0, 512, 1024, 64, GRAY);
				DrawRectangle(0, 576, 1024, 64, GRAY);
				DrawRectangle(0, 640, 1024, 64, GRAY);
				DrawRectangle(0, 704, 1024, 64, GRAY);
				DrawRectangle(0, 768, 1024, 64, GRAY);
				DrawRectangle(0, 832, 1024, 64, GRAY);

				//Start zone
				DrawRectangle(0, 896, 1024, 64, DARKGREEN);
				DrawRectangle(0, 960, 1024, 64, DARKGREEN);
			}

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
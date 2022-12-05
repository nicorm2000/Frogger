#include "Window/PlayGame.h"
#include "Objects/Frog.h"

#include "raylib.h"

static void Initialize();

static void Close();

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

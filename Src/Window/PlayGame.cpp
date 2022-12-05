#include "Window/PlayGame.h"
#include "raylib.h"

static void Initialize();

static void Close();

void GameLoop()
{
	Initialize();
	HideCursor();

	SetExitKey(KEY_NULL);

	bool playingGame = true;

	while (playingGame && !WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

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

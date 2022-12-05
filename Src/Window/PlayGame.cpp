#include "Window/PlayGame.h"
#include "raylib.h"

static void Initialize();

static void Close();

void GameLoop()
{
	Initialize();
	HideCursor();
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

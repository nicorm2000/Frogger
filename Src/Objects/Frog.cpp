#include "Frog.h"
#include "raylib.h"

Frog CreateFrog(Frog& frog)
{
	frog.frogPosition.x = 480;
	frog.frogPosition.y = 960;
	frog.frogSize.x = 64;
	frog.frogSize.y = 64;
	frog.isAlive = true;
	frog.frogColor = GREEN;

	return frog;
}

void DrawFrog(Frog frog)
{
	DrawRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, frog.frogColor);
}
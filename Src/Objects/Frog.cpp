#include "Frog.h"
#include "raylib.h"

Frog CreateFrog(Frog& frog)
{
	frog.frogPosition.x = 486;
	frog.frogPosition.y = 960;
	frog.frogSize.x = 50;
	frog.frogSize.y = 50;
	frog.isAlive = true;
	frog.frogColor = GREEN;

	return frog;
}

void DrawFrog(Frog frog)
{
	DrawRectangle(static_cast<int>(frog.frogPosition.x), static_cast<int>(frog.frogPosition.y), static_cast<int>(frog.frogSize.x), static_cast<int>(frog.frogSize.y), frog.frogColor);
}
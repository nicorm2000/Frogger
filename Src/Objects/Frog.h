#pragma once
#include "raylib.h"

struct Frog
{
	Vector2 frogPsition{};
	Vector2 frogSize;
	bool isAlive;
	Color frogColor;
	Texture frogTexture;
};

Frog CreateFrog(Frog& frog);

void DrawFrog(Frog frog);
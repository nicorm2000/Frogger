#pragma once
#include "raylib.h"

struct Frog
{
	Vector2 frogPosition{};
	Vector2 frogSize;
	bool isAlive;
	Color frogColor;
	Texture frogTexture;
};

Frog CreateFrog(Frog& frog);

void DrawFrog(Frog frog);
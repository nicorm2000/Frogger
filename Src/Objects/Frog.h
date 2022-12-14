#pragma once

#include "raylib.h"

namespace game
{
	struct Frog
	{
		Vector2 frogPosition{};
		Vector2 frogSize;
		int frogLives;
		bool isAlive;
		Color frogColor;
		Texture frogTexture;
	};

	Frog CreateFrog(Frog& frog);

	void DrawFrog(Frog frog);
}
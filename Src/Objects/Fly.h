#pragma once

#include "raylib.h"

namespace game
{
	struct Fly
	{
		Vector2 flyPosition{};
		Vector2 flySize;
		bool isFlyPicked;
		Color flyColor;
		Texture flyTexture;
	};

	Fly CreateFly(Fly& fly);

	void DrawFly(Fly fly);
}
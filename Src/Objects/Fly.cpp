#include "Objects/Fly.h"

namespace game
{
	Fly CreateFly(Fly& fly, float posX)
	{
		fly.flyPosition.x = posX;
		fly.flyPosition.y = 8;
		fly.flySize.x = 40;
		fly.flySize.y = 45;
		fly.isFlyPicked = false;
		fly.flyColor = WHITE;
		fly.flyTexture = LoadTexture("Resources/Textures/fly.png");

		return fly;
	}

	void DrawFly(Fly fly)
	{
		//DrawRectangle(static_cast<int>(fly.flyPosition.x), static_cast<int>(fly.flyPosition.y), static_cast<int>(fly.flySize.x), static_cast<int>(fly.flySize.y), fly.flyColor);
		DrawTexture(fly.flyTexture, static_cast<int>(fly.flyPosition.x), static_cast<int>(fly.flyPosition.y), fly.flyColor);
	}
}
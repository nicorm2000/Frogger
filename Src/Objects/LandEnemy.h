#pragma once
#include "raylib.h"

namespace game
{
	struct LandEnemy
	{
		Vector2 landEnemyPosition{};
		Vector2 landEnemySize;
		Vector2 landEnemySpeed{};
		Color landEnemyColor;
		Texture landEnemyTexture;
	};

	LandEnemy CreateCar(LandEnemy& landEnemy);

	LandEnemy CreateFastCar(LandEnemy& landEnemy);

	LandEnemy CreateVan(LandEnemy& landEnemy);

	LandEnemy CreateBus(LandEnemy& landEnemy);
	
	LandEnemy CreateTruck(LandEnemy& landEnemy);

	void DrawLandEnemy(LandEnemy landEnemy);
}
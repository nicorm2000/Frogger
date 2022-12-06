#pragma once
#include "raylib.h"

namespace game
{
	enum class LandVehicles
	{
		Motorcycle = 0,
		Car,
		FastCar,
		Van,
		Bus,
		Truck
	};

	struct LandEnemy
	{
		Vector2 landEnemyPosition{};
		Vector2 landEnemySize;
		float landEnemySpeed;
		Color landEnemyColor;
		Texture landEnemyTexture;
	};

	LandEnemy CreateVehicle(LandVehicles& landVehicles, LandEnemy& landEnemy);

	LandEnemy CreateMotorcycle(LandEnemy& landEnemy);
	
	LandEnemy CreateCar(LandEnemy& landEnemy);

	LandEnemy CreateFastCar(LandEnemy& landEnemy);

	LandEnemy CreateVan(LandEnemy& landEnemy);

	LandEnemy CreateBus(LandEnemy& landEnemy);
	
	LandEnemy CreateTruck(LandEnemy& landEnemy);

	void DrawLandEnemy(LandEnemy landEnemy);
}
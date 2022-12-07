#pragma once

#include "raylib.h"

namespace game
{
	const int MOTORCYCLE_COUNT = 3;
	const int CAR_COUNT = 3;
	const int FAST_CAR_COUNT = 3;
	const int VAN_COUNT = 3;
	const int BUS_COUNT = 3;
	const int TRUCK_COUNT = 3;

	enum class Vehicles
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
		Vector2 landEnemySize{};
		float landEnemySpeed;
		Color landEnemyColor;
		Texture landEnemyTexture;
	};
	
	LandEnemy CreateVehicle(Vehicles vehicle, int distance, int speed);
	 /*
	LandEnemy CreateMotorcycle(LandEnemy& landEnemy);
	
	LandEnemy CreateCar(LandEnemy& landEnemy);

	LandEnemy CreateFastCar(LandEnemy& landEnemy);

	LandEnemy CreateVan(LandEnemy& landEnemy);

	LandEnemy CreateBus(LandEnemy& landEnemy);
	
	LandEnemy CreateTruck(LandEnemy& landEnemy);
	*/
	void DrawLandEnemy(LandEnemy landEnemy);
}
#include "Objects/LandEnemy.h"
#include "raylib.h"

namespace game
{
	LandEnemy CreateVehicle(Vehicles vehicle, int distance, int speed)
	{
		LandEnemy landEnemy;

		switch (vehicle)
		{
			case game::Vehicles::Motorcycle:

				landEnemy.landEnemyPosition.x = -150 + distance;
				landEnemy.landEnemyPosition.y = 512;
				landEnemy.landEnemySize.x = 60;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = 250 + speed;
				landEnemy.landEnemyColor = RED;

				break;

			case game::Vehicles::Car:

				landEnemy.landEnemyPosition.x = 1124 + distance;
				landEnemy.landEnemyPosition.y = 832;
				landEnemy.landEnemySize.x = 80;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = -250 + speed;
				landEnemy.landEnemyColor = BLUE;

				break;
			
			case game::Vehicles::FastCar:
				
				landEnemy.landEnemyPosition.x = -150 + distance;
				landEnemy.landEnemyPosition.y = 768;
				landEnemy.landEnemySize.x = 80;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = 350 + speed;
				landEnemy.landEnemyColor = ORANGE;
				
				break;
			
			case game::Vehicles::Van:
				
				landEnemy.landEnemyPosition.x = 1124 + distance;
				landEnemy.landEnemyPosition.y = 704;
				landEnemy.landEnemySize.x = 100;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = -230 + speed;
				landEnemy.landEnemyColor = PURPLE;
				
				break;
			
			case game::Vehicles::Bus:
				
				landEnemy.landEnemyPosition.x = -150 + distance;
				landEnemy.landEnemyPosition.y = 640;
				landEnemy.landEnemySize.x = 150;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = 170 + speed;
				landEnemy.landEnemyColor = YELLOW;
				
				break;
			
			case game::Vehicles::Truck:
				
				landEnemy.landEnemyPosition.x = 1124 + distance;
				landEnemy.landEnemyPosition.y = 576;
				landEnemy.landEnemySize.x = 200;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = -150 + speed;
				landEnemy.landEnemyColor = MAGENTA;
				
				break;
			
			default:
				
				landEnemy = CreateVehicle(Vehicles::Motorcycle, distance, speed);

				break;
		}

		return landEnemy;
	}

	/*LandEnemy CreateMotorcycle(LandEnemy& landEnemy)
	{
		landEnemy.landEnemyPosition.x = -150;
		landEnemy.landEnemyPosition.y = 512;
		landEnemy.landEnemySize.x = 60;
		landEnemy.landEnemySize.y = 60;
		landEnemy.landEnemySpeed = 250;
		landEnemy.landEnemyColor = RED;

		return landEnemy;
	}

	LandEnemy CreateCar(LandEnemy& landEnemy)
	{
		landEnemy.landEnemyPosition.x = 1124;
		landEnemy.landEnemyPosition.y = 832;
		landEnemy.landEnemySize.x = 80;
		landEnemy.landEnemySize.y = 60;
		landEnemy.landEnemySpeed = -250;
		landEnemy.landEnemyColor = BLUE;

		return landEnemy;
	}

	LandEnemy CreateFastCar(LandEnemy& landEnemy)
	{
		landEnemy.landEnemyPosition.x = -150;
		landEnemy.landEnemyPosition.y = 768;
		landEnemy.landEnemySize.x = 80;
		landEnemy.landEnemySize.y = 60;
		landEnemy.landEnemySpeed = 350;
		landEnemy.landEnemyColor = ORANGE;

		return landEnemy;
	}

	LandEnemy CreateVan(LandEnemy& landEnemy)
	{
		landEnemy.landEnemyPosition.x = 1124;
		landEnemy.landEnemyPosition.y = 704;
		landEnemy.landEnemySize.x = 100;
		landEnemy.landEnemySize.y = 60;
		landEnemy.landEnemySpeed = -230;
		landEnemy.landEnemyColor = PURPLE;

		return landEnemy;
	}

	LandEnemy CreateBus(LandEnemy& landEnemy)
	{
		landEnemy.landEnemyPosition.x = -150;
		landEnemy.landEnemyPosition.y = 640;
		landEnemy.landEnemySize.x = 150;
		landEnemy.landEnemySize.y = 60;
		landEnemy.landEnemySpeed = 170;
		landEnemy.landEnemyColor = YELLOW;

		return landEnemy;
	}

	LandEnemy CreateTruck(LandEnemy& landEnemy)
	{
		landEnemy.landEnemyPosition.x = 1124;
		landEnemy.landEnemyPosition.y = 576;
		landEnemy.landEnemySize.x = 200;
		landEnemy.landEnemySize.y = 60;
		landEnemy.landEnemySpeed = -150;
		landEnemy.landEnemyColor = MAGENTA;

		return landEnemy;
	}
	*/
	void DrawLandEnemy(LandEnemy landEnemy)
	{
		DrawRectangle(static_cast<int>(landEnemy.landEnemyPosition.x), static_cast<int>(landEnemy.landEnemyPosition.y), static_cast<int>(landEnemy.landEnemySize.x), static_cast<int>(landEnemy.landEnemySize.y), landEnemy.landEnemyColor);
	}
}
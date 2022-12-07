#include "Objects/LandEnemy.h"
#include "raylib.h"

namespace game
{
	LandEnemy CreateVehicle(Vehicles vehicle, float distance)
	{
		LandEnemy landEnemy;

		switch (vehicle)
		{
			case game::Vehicles::Motorcycle:

				landEnemy.landEnemyPosition.x = -150 + distance;
				landEnemy.landEnemyPosition.y = 512;
				landEnemy.landEnemySize.x = 60;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = 250;
				landEnemy.landEnemyColor = RED;

				break;

			case game::Vehicles::Car:

				landEnemy.landEnemyPosition.x = 1124 + distance;
				landEnemy.landEnemyPosition.y = 832;
				landEnemy.landEnemySize.x = 80;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = -250;
				landEnemy.landEnemyColor = BLUE;

				break;
			
			case game::Vehicles::FastCar:
				
				landEnemy.landEnemyPosition.x = -150 + distance;
				landEnemy.landEnemyPosition.y = 768;
				landEnemy.landEnemySize.x = 80;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = 350;
				landEnemy.landEnemyColor = ORANGE;
				
				break;
			
			case game::Vehicles::Van:
				
				landEnemy.landEnemyPosition.x = 1124 + distance;
				landEnemy.landEnemyPosition.y = 704;
				landEnemy.landEnemySize.x = 100;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = -230;
				landEnemy.landEnemyColor = PURPLE;
				
				break;
			
			case game::Vehicles::Bus:
				
				landEnemy.landEnemyPosition.x = -150 + distance;
				landEnemy.landEnemyPosition.y = 640;
				landEnemy.landEnemySize.x = 150;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = 170;
				landEnemy.landEnemyColor = YELLOW;
				
				break;
			
			case game::Vehicles::Truck:
				
				landEnemy.landEnemyPosition.x = 1124 + distance;
				landEnemy.landEnemyPosition.y = 576;
				landEnemy.landEnemySize.x = 200;
				landEnemy.landEnemySize.y = 60;
				landEnemy.landEnemySpeed = -150;
				landEnemy.landEnemyColor = MAGENTA;
				
				break;
			
			default:
				
				landEnemy = CreateVehicle(Vehicles::Motorcycle, distance);//The function is called again so there is always an object called

				break;
		}

		return landEnemy;
	}

	void DrawLandEnemy(LandEnemy landEnemy)
	{
		DrawRectangle(static_cast<int>(landEnemy.landEnemyPosition.x), static_cast<int>(landEnemy.landEnemyPosition.y), static_cast<int>(landEnemy.landEnemySize.x), static_cast<int>(landEnemy.landEnemySize.y), landEnemy.landEnemyColor);
	}
}
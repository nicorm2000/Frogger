#include "Objects/LandEnemy.h"
#include "raylib.h"

namespace game
{
	LandEnemy CreateMotorcycle(LandEnemy& landEnemy)
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

	void DrawLandEnemy(LandEnemy landEnemy)
	{
		DrawRectangle(static_cast<int>(landEnemy.landEnemyPosition.x), static_cast<int>(landEnemy.landEnemyPosition.y), static_cast<int>(landEnemy.landEnemySize.x), static_cast<int>(landEnemy.landEnemySize.y), landEnemy.landEnemyColor);
	}
}
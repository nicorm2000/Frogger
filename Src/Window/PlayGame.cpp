#include "Window/PlayGame.h"
#include "Objects/Frog.h"
#include "Objects/LandEnemy.h"

#include "raylib.h"

namespace game
{

	static void Initialize();

	static void Close();

	void LandEnemyTp(LandEnemy& landEnemy);

	void CheckPlayerInput(Frog& frog, bool& playingGame);

	void GameLoop()
	{
		Initialize();
		//HideCursor();
		SetExitKey(KEY_NULL);

		bool playingGame = true;

		Frog frog;

		LandEnemy motorcycle;
		LandEnemy car;
		LandEnemy fastCar;
		LandEnemy van;
		LandEnemy bus;
		LandEnemy truck;

		CreateFrog(frog);

		CreateMotorcycle(motorcycle);
		CreateCar(car);
		CreateFastCar(fastCar);
		CreateVan(van);
		CreateBus(bus);
		CreateTruck(truck);

		while (playingGame && !WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(BLACK);

			//Logic

			CheckPlayerInput(frog, playingGame);
			LandEnemyTp(motorcycle);
			LandEnemyTp(car);
			LandEnemyTp(fastCar);
			LandEnemyTp(van);
			LandEnemyTp(bus);
			LandEnemyTp(truck);

			//Draw
			
			//Map
			{
				DrawRectangle(0, 0, 1024, 64, DARKGRAY);

				//Objective zone
				DrawRectangle(95, 0, 64, 64, LIME);
				DrawRectangle(287, 0, 64, 64, LIME);
				DrawRectangle(479, 0, 64, 64, LIME);
				DrawRectangle(671, 0, 64, 64, LIME);
				DrawRectangle(863, 0, 64, 64, LIME);

				//Water
				DrawRectangle(0, 64, 1024, 64, SKYBLUE);
				DrawRectangle(0, 128, 1024, 64, SKYBLUE);
				DrawRectangle(0, 192, 1024, 64, SKYBLUE);
				DrawRectangle(0, 256, 1024, 64, SKYBLUE);
				DrawRectangle(0, 320, 1024, 64, SKYBLUE);
				DrawRectangle(0, 384, 1024, 64, SKYBLUE);

				//Sidewalk
				DrawRectangle(0, 448, 1024, 64, LIGHTGRAY);

				//Street
				DrawRectangle(0, 512, 1024, 64, GRAY);
				DrawRectangle(0, 576, 1024, 64, GRAY);
				DrawRectangle(0, 640, 1024, 64, GRAY);
				DrawRectangle(0, 704, 1024, 64, GRAY);
				DrawRectangle(0, 768, 1024, 64, GRAY);
				DrawRectangle(0, 832, 1024, 64, GRAY);

				//Sidewalk
				DrawRectangle(0, 896, 1024, 64, LIGHTGRAY);
				
				//Start zone
				DrawRectangle(0, 960, 1024, 64, DARKGREEN);
			}

			DrawRectangle(510, 0, 2, 1024, WHITE);

			DrawLandEnemy(motorcycle);
			DrawLandEnemy(car);
			DrawLandEnemy(fastCar);
			DrawLandEnemy(van);
			DrawLandEnemy(bus);
			DrawLandEnemy(truck);

			if (frog.isAlive)
			{
				DrawFrog(frog);
			}

			EndDrawing();
		}

		Close();
	}

	static void Initialize()
	{
		InitWindow(1024, 1024, "Frogger 0.1");
	}

	static void Close()
	{
		CloseWindow();
	}

	void LandEnemyTp(LandEnemy& landEnemy)
	{
		if (landEnemy.landEnemySpeed < 0)
		{
			if (landEnemy.landEnemyPosition.x < -200)
			{
				landEnemy.landEnemyPosition.x = static_cast<float>(GetScreenWidth()) + 50;
			}
		}
		else
		{
			if (landEnemy.landEnemyPosition.x > GetScreenWidth() + 200)
			{
				landEnemy.landEnemyPosition.x = -200;
			}
		}
	}

	void CheckPlayerInput(Frog& frog, bool& playingGame)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			playingGame = false;
		}

		if (IsKeyPressed(KEY_UP))
		{
			if (frog.frogPosition.y >= 64)
			{
				frog.frogPosition.y -= 64;
			}
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			if (frog.frogPosition.y <= 959)
			{
				frog.frogPosition.y += 64;
			}
		}

		if (IsKeyPressed(KEY_RIGHT))
		{
			if (frog.frogPosition.x <= 933)
			{
				frog.frogPosition.x += 64;
			}
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			if (frog.frogPosition.x >= 39)
			{
				frog.frogPosition.x -= 64;
			}
		}
	}
}
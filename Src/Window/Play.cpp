#include "Window/MainMenu.h"
#include "Window/Play.h"
#include "Window/HowToPlay.h"
#include "Window/Credits.h"
#include "Objects/Frog.h"
#include "Objects/Log.h"
#include "Objects/LandEnemy.h"

#include "raylib.h"

namespace game
{

	static void Initialize();

	static void Close();

	void LogTp(Log& log);

	void LandEnemyTp(LandEnemy& landEnemy);

	void CheckPlayerInput(Frog& frog, bool& playingGame);

	bool CollisionRectangleRectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);

	void GameCollisions(Frog& frog, LandEnemy landEnemy);

	void Game()
	{
		Initialize();
		//HideCursor();
		SetExitKey(KEY_NULL);

		bool playingGame = true;
		bool isPaused = false;
		bool exitWindow = false;
		bool gameFinished = false;

		GameState gameState = GameState::GAMETITLE;

		Frog frog;

		Log totalLogs[LOG_COUNT];
		//Log totalLogs2[LOG_COUNT2];

		int auxLogCount = 0;

		Log smallLog[SMALL_LOG_COUNT];
		Log smallLog2[SMALL_LOG_COUNT2];
		Log mediumLog[MEDIUM_LOG_COUNT];
		Log mediumLog2[MEDIUM_LOG_COUNT2];
		Log bigLog[BIG_LOG_COUNT];
		Log bigLog2[BIG_LOG_COUNT2];

		LandEnemy landEnemies[LAND_ENEMIES_COUNT];

		int auxEnemyCount = 0;

		LandEnemy motorcycle[MOTORCYCLE_COUNT];
		LandEnemy car[CAR_COUNT];
		LandEnemy fastCar[FAST_CAR_COUNT];
		LandEnemy van[VAN_COUNT];
		LandEnemy bus[BUS_COUNT];
		LandEnemy truck[TRUCK_COUNT];

		CreateFrog(frog);
		
		//Logs
		{
			for (int i = 0; i < SMALL_LOG_COUNT; i++)
			{
				smallLog[i] = CreateLog(Logs::Small, static_cast<float>(i * -500));

				totalLogs[auxLogCount] = smallLog[i];
				auxLogCount++;
			}

			for (int i = 0; i < SMALL_LOG_COUNT2; i++)
			{
				smallLog2[i] = CreateLog(Logs::Small, static_cast<float>(i * 500));
				smallLog2[i].logPosition.y = 66;
				smallLog2[i].logSpeed = -200;

				totalLogs[auxLogCount] = smallLog2[i];
				auxLogCount++;
			}

			for (int i = 0; i < MEDIUM_LOG_COUNT; i++)
			{
				mediumLog[i] = CreateLog(Logs::Medium, static_cast<float>(i * -500));

				totalLogs[auxLogCount] = mediumLog[i];
				auxLogCount++;
			}

			for (int i = 0; i < MEDIUM_LOG_COUNT2; i++)
			{
				mediumLog2[i] = CreateLog(Logs::Medium, static_cast<float>(i * 500));
				mediumLog2[i].logPosition.y = 130;
				mediumLog2[i].logSpeed = 175;

				totalLogs[auxLogCount] = mediumLog2[i];
				auxLogCount++;
			}

			for (int i = 0; i < BIG_LOG_COUNT; i++)
			{
				bigLog[i] = CreateLog(Logs::Big, static_cast<float>(i * -500));

				totalLogs[auxLogCount] = bigLog[i];
				auxLogCount++;
			}

			for (int i = 0; i < BIG_LOG_COUNT2; i++)
			{
				bigLog2[i] = CreateLog(Logs::Big, static_cast<float>(i * 500));
				bigLog2[i].logPosition.y = 194;
				bigLog2[i].logSpeed = -150;

				totalLogs[auxLogCount] = bigLog2[i];
				auxLogCount++;
			}
		}

		//Land Enemies
		{
			for (int i = 0; i < MOTORCYCLE_COUNT; i++)
			{
				motorcycle[i] = CreateVehicle(Vehicles::Motorcycle, static_cast<float>(i * -500));

				landEnemies[auxEnemyCount] = motorcycle[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < CAR_COUNT; i++)
			{
				car[i] = CreateVehicle(Vehicles::Car, static_cast<float>(i * -500));

				landEnemies[auxEnemyCount] = car[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < FAST_CAR_COUNT; i++)
			{
				fastCar[i] = CreateVehicle(Vehicles::FastCar, static_cast<float>(i * -500));

				landEnemies[auxEnemyCount] = fastCar[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < VAN_COUNT; i++)
			{
				van[i] = CreateVehicle(Vehicles::Van, static_cast<float>(i * -500));

				landEnemies[auxEnemyCount] = van[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < BUS_COUNT; i++)
			{
				bus[i] = CreateVehicle(Vehicles::Bus, static_cast<float>(i * -500));

				landEnemies[auxEnemyCount] = bus[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < TRUCK_COUNT; i++)
			{
				truck[i] = CreateVehicle(Vehicles::Truck, static_cast<float>(i * -400));

				landEnemies[auxEnemyCount] = truck[i];
				auxEnemyCount++;
			}
		}
		
		Vector2 mousePosition = GetMousePosition();

		while (playingGame && !WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(BLACK);

			switch (gameState)
			{
				case game::GameState::GAMETITLE:

					////Logic

					mousePosition = GetMousePosition();

					MainMenuLogic(mousePosition, gameState);

					////Draw

					MainMenuDraw();

					break;

				case game::GameState::GAME:
					
					////Logic

					mousePosition = GetMousePosition();
					
					if (!isPaused)
					{
						if (frog.isAlive)
						{
							CheckPlayerInput(frog, playingGame);
						}
						
						for (int i = 0; i < LAND_ENEMIES_COUNT; i++)
						{
							GameCollisions(frog, landEnemies[i]);
						}

						//Log Loigc

						//Logs

						for (int i = 0; i < LOG_COUNT; i++)
						{
							totalLogs[i].logPosition.x += totalLogs[i].logSpeed * GetFrameTime();

							LogTp(totalLogs[i]);
						}

						//Enemy Logic

						for (int i = 0; i < LAND_ENEMIES_COUNT; i++)
						{
							landEnemies[i].landEnemyPosition.x += landEnemies[i].landEnemySpeed * GetFrameTime();

							LandEnemyTp(landEnemies[i]);
						}
					}

					//Pause Logic

					if (IsKeyPressed(KEY_ESCAPE) && !gameFinished)
					{
						isPaused = true;
						exitWindow = true;
					}

					if (exitWindow)
					{
						if (CheckCollisionPointRec(mousePosition, { 350, 525, 150, 100 }))
						{
							if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
							{
								exitWindow = false;
								isPaused = !isPaused;
							}
						}
						if (CheckCollisionPointRec(mousePosition, { 530, 525, 150, 100 }))
						{
							if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
							{
								gameState = GameState::GAMETITLE;

								exitWindow = false;
								isPaused = !isPaused;
							}
						}
					}
					////Draw

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

					//Draw lives

					DrawText(TextFormat("Lives:%i", frog.frogLives), 10, 965, 60, BLACK);

					//Draw log

					for (int i = 0; i < LOG_COUNT; i++)
					{
						DrawLog(totalLogs[i]);
					}

					//Draw enemy

					for (int i = 0; i < LAND_ENEMIES_COUNT; i++)
					{
						DrawLandEnemy(landEnemies[i]);
					}

					//Draw player

					if (frog.isAlive)
					{
						DrawFrog(frog);
					}

					//Draw Pause

					if (exitWindow)
					{
						DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 250, static_cast<float>(GetScreenHeight() / 2) - 200, 500, 400 }, 0.5f, 1, BLACK);
						DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 245, static_cast<float>(GetScreenHeight() / 2) - 195, 490, 390 }, 0.5f, 1, WHITE);

						DrawText("Do you want to", static_cast<int>(GetScreenWidth() - 705), static_cast<int>(GetScreenHeight() / 2) - 150, 51, BLACK);
						DrawText("keep playing?", static_cast<int>(GetScreenWidth() - 685), static_cast<int>(GetScreenHeight() / 2) - 80, 51, BLACK);

						DrawRectangleRounded({ 350, 525, 150, 100 }, 0.5f, 1, BLACK);
						DrawRectangleRounded({ 355, 530, 140, 90 }, 0.5f, 1, WHITE);

						DrawText("YES", 390, 560, 35, BLACK);

						DrawRectangleRounded({ 530, 525, 150, 100 }, 0.5f, 1, BLACK);
						DrawRectangleRounded({ 535, 530, 140, 90 }, 0.5f, 1, WHITE);

						DrawText("NO", 580, 560, 35, BLACK);
					}

					break;

				case game::GameState::HOWTOPLAY:
					
					////Logic

					mousePosition = GetMousePosition();

					HowToPlayLogic(mousePosition, gameState);

					////Draw

					HowToPlayDraw();

					break;

				case game::GameState::CREDITS:
					
					////Logic

					mousePosition = GetMousePosition();
					
					CreditsLogic(mousePosition, gameState);

					////Draw

					CreditsDraw();

					break;

				case game::GameState::EXIT:

					playingGame = false;

					break;
			}

			EndDrawing();
		}

		Close();
	}

	static void Initialize()
	{
		InitWindow(1024, 1024, "Frogger 0.2");
	}

	static void Close()
	{
		CloseWindow();
	}

	void LogTp(Log& log)
	{
		if (log.logSpeed < 0)
		{
			if (log.logPosition.x < -310)
			{
				log.logPosition.x = static_cast<float>(GetScreenWidth()) + 50;
			}
		}
		else
		{
			if (log.logPosition.x > GetScreenWidth() + 200)
			{
				log.logPosition.x = -310;
			}
		}
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

	bool CollisionRectangleRectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
	{
		if (r1x + r1w >= r2x && r1x <= r2x + r2w && r1y + r1h >= r2y && r1y <= r2y + r2h)
		{
			return true;
		}
		return false;
	}

	void GameCollisions(Frog& frog, LandEnemy landEnemy)
	{
		if (frog.isAlive)
		{
			if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, landEnemy.landEnemyPosition.x, landEnemy.landEnemyPosition.y, landEnemy.landEnemySize.x, landEnemy.landEnemySize.y))
			{
				frog.frogLives--;
				
				frog.frogPosition.x = 486;
				frog.frogPosition.y = 967.5f;

				if (frog.frogLives <= 0)
				{
					frog.isAlive = false;
				}
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
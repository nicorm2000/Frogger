#include "MainMenu.h"
#include "Window/Play.h"
#include "HowToPlay.h"
#include "Credits.h"
#include "Objects/Frog.h"
#include "Objects/LandEnemy.h"

#include "raylib.h"

namespace game
{

	static void Initialize();

	static void Close();

	void LandEnemyTp(LandEnemy& landEnemy);

	void CheckPlayerInput(Frog& frog, bool& playingGame);

	bool CollisionRectangleRectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);

	void GameCollisions(Frog& frog, LandEnemy landEnemy);

	void GameLoop()
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

						GameCollisions(frog, motorcycle);
						GameCollisions(frog, car);
						GameCollisions(frog, fastCar);
						GameCollisions(frog, van);
						GameCollisions(frog, bus);
						GameCollisions(frog, truck);

						//Enemy Logic
						motorcycle.landEnemyPosition.x += motorcycle.landEnemySpeed * GetFrameTime();
						car.landEnemyPosition.x += car.landEnemySpeed * GetFrameTime();
						fastCar.landEnemyPosition.x += fastCar.landEnemySpeed * GetFrameTime();
						van.landEnemyPosition.x += van.landEnemySpeed * GetFrameTime();
						bus.landEnemyPosition.x += bus.landEnemySpeed * GetFrameTime();
						truck.landEnemyPosition.x += truck.landEnemySpeed * GetFrameTime();

						LandEnemyTp(motorcycle);
						LandEnemyTp(car);
						LandEnemyTp(fastCar);
						LandEnemyTp(van);
						LandEnemyTp(bus);
						LandEnemyTp(truck);
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

					DrawText(TextFormat("Lives:%i", frog.frogLives), 10, 965, 60, BLACK);

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
#include "Window/MainMenu.h"
#include "Window/Play.h"
#include "Window/HowToPlay.h"
#include "Window/Credits.h"
#include "Objects/Frog.h"
#include "Objects/Log.h"
#include "Objects/LandEnemy.h"
#include "Objects/Water.h"
#include "Objects/Fly.h"

#include "raylib.h"

namespace game
{
	static void Initialize();

	static void Close();

	void LogTp(Log& log);

	void LandEnemyTp(LandEnemy& landEnemy);

	void CheckPlayerInput(Frog& frog, Sound frogJump);

	bool CollisionRectangleRectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);

	void LandGameCollisions(Frog& frog, LandEnemy landEnemy, float& timer, Sound frogSplat);

	void WaterGameCollisions(Frog& frog, Water water, Log totalLogs[], float& timer, Sound frogDrown);

	bool LogCollisions(Frog& frog, Log log);

	void FlyCollisions(Frog& frog, Fly& fly, int& fliesPickedUp, float& timer, Sound frogPickUpFly);

	void Respawn(Frog& frog, float& timer);

	void TpBackToStart(Frog& frog);

	void ResetGame(Frog& frog, Fly& fly, float& timer, int& fliesPickedUp);

	void UnloadDataPlay(Texture2D mouse, Texture2D bg, Frog frog, Log totalLogs[], LandEnemy landEnemies[], Fly flies[], Font gameFont, Sound frogJump, Sound frogSplat, Sound frogDrown, Sound frogPickUpFly, Sound frogRibbitClick, Music bgMusic);

	void Game()
	{
		Initialize();
		HideCursor();
		SetExitKey(KEY_NULL);

		bool playingGame = true;
		bool isPaused = false;
		bool exitWindow = false;
		bool gameFinished = false;

		float timer = 30.0f;

		GameState gameState = GameState::GAMETITLE;

		Texture2D mouse = LoadTexture("Resources/Textures/mouse.png");
		Texture2D bg = LoadTexture("Resources/Textures/bg.png");
			
		Font gameFont = LoadFont("Resources/Fonts/Abalone Smile.otf");
		
		Sound frogJump = LoadSound("Resources/Sounds/zapsplat_cartoon_spring_boing_jump_002_88903.wav");
		Sound frogSplat = LoadSound("Resources/Sounds/87535__whiprealgood__splat.wav");
		Sound frogDrown = LoadSound("Resources/Sounds/657930__matrixxx__cartoon-drowning-02.wav");
		Sound frogPickUpFly = LoadSound("Resources/Sounds/646671__sounddesignforyou__coin-pickup-sfx-3.wav");
		Sound frogRibbitClick = LoadSound("Resources/Sounds/Frog-sound-ribbit.wav");

		Music bgMusic = LoadMusicStream("Resources/Sounds/Video Game Music - Dar Golan - 200bpm - 01-11.mp3");

		Frog frog;

		Water water;

		Fly flies[FLIES_COUNT];

		int fliesPickedUp = 0;

		Log totalLogs[LOG_COUNT];

		Log smallLog[SMALL_LOG_COUNT];
		Log smallLog2[SMALL_LOG_COUNT2];
		Log mediumLog[MEDIUM_LOG_COUNT];
		Log mediumLog2[MEDIUM_LOG_COUNT2];
		Log bigLog[BIG_LOG_COUNT];
		Log bigLog2[BIG_LOG_COUNT2];

		int auxLogCount = 0;

		LandEnemy landEnemies[LAND_ENEMIES_COUNT];

		LandEnemy motorcycle[MOTORCYCLE_COUNT];
		LandEnemy car[CAR_COUNT];
		LandEnemy fastCar[FAST_CAR_COUNT];
		LandEnemy van[VAN_COUNT];
		LandEnemy bus[BUS_COUNT];
		LandEnemy truck[TRUCK_COUNT];

		int auxEnemyCount = 0;

		CreateFrog(frog);
		
		CreateWater(water);

		int currentDistance = 0;

		for (int i = 0; i < FLIES_COUNT; i++)
		{
			CreateFly(flies[i], static_cast<float>(106 + currentDistance));

			currentDistance += SPACE_BETWEEN_FLIES;
		}

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
				mediumLog[i] = CreateLog(Logs::Medium, static_cast<float>(i * 500));

				totalLogs[auxLogCount] = mediumLog[i];
				auxLogCount++;
			}

			for (int i = 0; i < MEDIUM_LOG_COUNT2; i++)
			{
				mediumLog2[i] = CreateLog(Logs::Medium, static_cast<float>(i * -500));
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

		PlayMusicStream(bgMusic);

		SetMusicVolume(bgMusic, 0.5f);

		while (playingGame && !WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(BLACK);

			UpdateMusicStream(bgMusic);

			switch (gameState)
			{
				case game::GameState::GAMETITLE:

					////Logic

					mousePosition = GetMousePosition();

					MainMenuLogic(mousePosition, gameState, frogRibbitClick);

					for (int i = 0; i < FLIES_COUNT; i++)
					{
						ResetGame(frog, flies[i], timer, fliesPickedUp);
					}

					////Draw

					MainMenuDraw();

					DrawTexture(mouse, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

					break;

				case game::GameState::GAME:
					
					////Logic

					mousePosition = GetMousePosition();

					if (fliesPickedUp != 5)
					{
						if (!isPaused)
						{
							if (frog.isAlive)
							{
								timer -= GetFrameTime();

								if (timer <= 0.0f)
								{
									Respawn(frog, timer);
								}

								CheckPlayerInput(frog, frogJump);

								for (int i = 0; i < LAND_ENEMIES_COUNT; i++)
								{
									LandGameCollisions(frog, landEnemies[i], timer, frogSplat);
								}

								WaterGameCollisions(frog, water, totalLogs, timer, frogDrown);

								for (int i = 0; i < FLIES_COUNT; i++)
								{
									if (!flies[i].isFlyPicked)
									{
										FlyCollisions(frog, flies[i], fliesPickedUp, timer, frogPickUpFly);
									}
								}
							}
							else if (!frog.isAlive)
							{
								PlaySound(frogRibbitClick);

								SetSoundVolume(frogRibbitClick, 1);
							}

							for (int i = 0; i < LOG_COUNT; i++)
							{
								totalLogs[i].logPosition.x += totalLogs[i].logSpeed * GetFrameTime();

								LogTp(totalLogs[i]);
							}

							for (int i = 0; i < LAND_ENEMIES_COUNT; i++)
							{
								landEnemies[i].landEnemyPosition.x += landEnemies[i].landEnemySpeed * GetFrameTime();

								LandEnemyTp(landEnemies[i]);
							}
						}
					}
					else
					{
						if (CheckCollisionPointRec(mousePosition, { 350, 525, 150, 100 }))
						{
							if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
							{
								PlaySound(frogRibbitClick);

								SetSoundVolume(frogRibbitClick, 1);

								gameState = GameState::GAME;
							}
						}
						if (CheckCollisionPointRec(mousePosition, { 530, 525, 150, 100 }))
						{
							if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
							{
								PlaySound(frogRibbitClick);

								SetSoundVolume(frogRibbitClick, 1);

								gameState = GameState::GAMETITLE;
							}
						}
					}

					//Pause Logic

					if (IsKeyPressed(KEY_ESCAPE) && !gameFinished)
					{
						PlaySound(frogRibbitClick);

						SetSoundVolume(frogRibbitClick, 1);

						isPaused = true;
						exitWindow = true;
					}

					if (exitWindow)
					{
						if (CheckCollisionPointRec(mousePosition, { 350, 525, 150, 100 }))
						{
							if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
							{
								PlaySound(frogRibbitClick);

								SetSoundVolume(frogRibbitClick, 1);

								exitWindow = false;
								isPaused = !isPaused;
							}
						}
						if (CheckCollisionPointRec(mousePosition, { 530, 525, 150, 100 }))
						{
							if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
							{
								PlaySound(frogRibbitClick);

								SetSoundVolume(frogRibbitClick, 1);

								gameState = GameState::GAMETITLE;

								exitWindow = false;
								isPaused = !isPaused;
							}
						}
					}
					////Draw

					//Map
					DrawMap(bg);
					
					for (int i = 0; i < FLIES_COUNT; i++)
					{
						if (!flies[i].isFlyPicked)
						{
							DrawFly(flies[i]);
						}
					}

					//Draw lives

					DrawTextEx(gameFont, TextFormat("Lives: %i", frog.frogLives), { 10, 955 }, 80, 0, BLACK);

					//Draw Points

					DrawTextEx(gameFont, TextFormat("Timer: %02.02f", timer), { 720, 955 }, 80, 0, BLACK);

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
						DrawExitWindow(gameFont);
					}

					//Win Menu
					if (fliesPickedUp == 5 && frog.isAlive)
					{
						DrawExitWindow(gameFont);
					}

					DrawTexture(mouse, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

					break;

				case game::GameState::HOWTOPLAY:
					
					////Logic

					mousePosition = GetMousePosition();

					HowToPlayLogic(mousePosition, gameState, frogRibbitClick);

					////Draw

					HowToPlayDraw();

					DrawTexture(mouse, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

					break;

				case game::GameState::CREDITS:
					
					////Logic

					mousePosition = GetMousePosition();
					
					CreditsLogic(mousePosition, gameState, frogRibbitClick);

					////Draw

					CreditsDraw();

					DrawTexture(mouse, static_cast<int>(mousePosition.x), static_cast<int>(mousePosition.y), WHITE);

					break;

				case game::GameState::EXIT:

					UnloadDataMainMenu(frogRibbitClick);
					UnloadDataPlay(mouse, bg, frog, totalLogs, landEnemies, flies, gameFont, frogJump, frogSplat, frogDrown, frogPickUpFly, frogRibbitClick, bgMusic);
					UnloadDataHowToPlay(frogRibbitClick);
					UnloadDataCredits(frogRibbitClick);
					
					playingGame = false;

					break;
			}

			EndDrawing();
		}

		Close();
	}

	static void Initialize()
	{
		InitWindow(1024, 1024, "Frogger 0.3");
		InitAudioDevice();
	}

	static void Close()
	{
		CloseAudioDevice();
		CloseWindow();
	}

	void DrawMap(Texture2D bg)
	{
		DrawTexture(bg, 0, 0, WHITE);
	}

	void DrawExitWindow(Font gameFont)
	{
		DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 250, static_cast<float>(GetScreenHeight() / 2) - 190, 500, 330 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 245, static_cast<float>(GetScreenHeight() / 2) - 185, 490, 320 }, 0.5f, 1, LIGHTGRAY);

		DrawTextPro(gameFont, "Do you want to", { static_cast<float>(GetScreenWidth() - 730), static_cast<float>(GetScreenHeight() / 2) - 150 }, { 0, 0 }, 0, 90, 0, BLACK);
		DrawTextPro(gameFont, "keep playing?", { static_cast<float>(GetScreenWidth() - 700), static_cast<float>(GetScreenHeight() / 2) - 80 }, { 0, 0 }, 0, 90, 0, BLACK);

		DrawRectangleRounded({ 350, 525, 150, 100 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ 355, 530, 140, 90 }, 0.5f, 1, GREEN);

		DrawTextPro(gameFont, "YES", { 375, 540 }, { 0, 0 }, 0, 80, 0, BLACK);

		DrawRectangleRounded({ 530, 525, 150, 100 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ 535, 530, 140, 90 }, 0.5f, 1, RED);

		DrawTextPro(gameFont, "NO", { 570, 540 }, { 0, 0 }, 0, 80, 0, BLACK);
	}

	void DrawWinMenu(Font gameFont)
	{
		DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 250, static_cast<float>(GetScreenHeight() / 2) - 190, 500, 330 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 245, static_cast<float>(GetScreenHeight() / 2) - 185, 490, 320 }, 0.5f, 1, LIGHTGRAY);

		DrawTextPro(gameFont, "You Won!", { static_cast<float>(GetScreenWidth() - 730), static_cast<float>(GetScreenHeight() / 2) - 150 }, { 0, 0 }, 0, 150, 0, BLACK);

		DrawRectangleRounded({ 350, 525, 150, 100 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ 355, 530, 140, 90 }, 0.5f, 1, GREEN);

		DrawTextPro(gameFont, "go back", { 365, 530 }, { 0, 0 }, 0, 50, 0, BLACK);
		DrawTextPro(gameFont, "to menu", { 355, 565 }, { 0, 0 }, 0, 50, 0, BLACK);

		DrawRectangleRounded({ 530, 525, 150, 100 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ 535, 530, 140, 90 }, 0.5f, 1, RED);

		DrawTextPro(gameFont, "exit", { 575, 530 }, { 0, 0 }, 0, 50, 0, BLACK);
		DrawTextPro(gameFont, "game", { 560, 565 }, { 0, 0 }, 0, 50, 0, BLACK);
	}

	void DrawLoseMenu(Font gameFont, int fliesPickedUp)
	{
		DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 250, static_cast<float>(GetScreenHeight() / 2) - 190, 500, 330 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ static_cast<float>(GetScreenWidth() / 2) - 245, static_cast<float>(GetScreenHeight() / 2) - 185, 490, 320 }, 0.5f, 1, LIGHTGRAY);

		DrawTextPro(gameFont, "You Lost!", { static_cast<float>(GetScreenWidth() - 650), static_cast<float>(GetScreenHeight() / 2) - 180 }, { 0, 0 }, 0, 100, 0, BLACK);
		DrawTextPro(gameFont, "You got", { static_cast<float>(GetScreenWidth() - 725), static_cast<float>(GetScreenHeight() / 2) - 80 }, { 0, 0 }, 0, 90, 0, BLACK);
		DrawTextPro(gameFont, TextFormat("%i", fliesPickedUp), { static_cast<float>(GetScreenWidth() - 475), static_cast<float>(GetScreenHeight() / 2) - 80 }, { 0, 0 }, 0, 90, 0, WHITE);
		DrawTextPro(gameFont, "flies", { static_cast<float>(GetScreenWidth() - 415), static_cast<float>(GetScreenHeight() / 2) - 80 }, { 0, 0 }, 0, 90, 0, BLACK);

		DrawRectangleRounded({ 350, 525, 150, 100 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ 355, 530, 140, 90 }, 0.5f, 1, GREEN);

		DrawTextPro(gameFont, "go back", { 365, 530 }, { 0, 0 }, 0, 50, 0, BLACK);
		DrawTextPro(gameFont, "to menu", { 355, 565 }, { 0, 0 }, 0, 50, 0, BLACK);

		DrawRectangleRounded({ 530, 525, 150, 100 }, 0.5f, 1, BLACK);
		DrawRectangleRounded({ 535, 530, 140, 90 }, 0.5f, 1, RED);

		DrawTextPro(gameFont, "exit", { 575, 530 }, { 0, 0 }, 0, 50, 0, BLACK);
		DrawTextPro(gameFont, "game", { 560, 565 }, { 0, 0 }, 0, 50, 0, BLACK);
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

	void Respawn(Frog& frog, float& timer)
	{
		timer = 30.0f;

		frog.frogLives--;

		frog.frogPosition.x = 486;
		frog.frogPosition.y = 967.5f;

		if (frog.frogLives <= 0)
		{
			frog.isAlive = false;
		}
	}

	void TpBackToStart(Frog& frog)
	{
		frog.frogPosition.x = 486;
		frog.frogPosition.y = 967.5f;
	}

	bool CollisionRectangleRectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
	{
		if (r1x + r1w >= r2x && r1x <= r2x + r2w && r1y + r1h >= r2y && r1y <= r2y + r2h)
		{
			return true;
		}

		return false;
	}

	void LandGameCollisions(Frog& frog, LandEnemy landEnemy, float& timer, Sound frogSplat)
	{
		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, landEnemy.landEnemyPosition.x, landEnemy.landEnemyPosition.y, landEnemy.landEnemySize.x, landEnemy.landEnemySize.y))
		{
			Respawn(frog, timer);

			//Splat Sound
			PlaySound(frogSplat);

			SetSoundVolume(frogSplat, 1);
		}
	}

	void WaterGameCollisions(Frog& frog, Water water, Log totalLogs[], float& timer, Sound frogDrown)
	{
		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, water.waterPosition.x, water.waterPosition.y, water.waterSize.x, water.waterSize.y))
		{
			bool frogOnLog = false;

			for (int i = 0; i < LOG_COUNT; i++)
			{
				frogOnLog = LogCollisions(frog, totalLogs[i]);

				if (frogOnLog)
				{
					break;
				}
			}

			if (!frogOnLog)
			{
				Respawn(frog, timer);

				//Drown Sound
				PlaySound(frogDrown);

				SetSoundVolume(frogDrown, 1);
			}
		}
	}

	bool LogCollisions(Frog& frog, Log log)
	{
		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, log.logPosition.x, log.logPosition.y, log.logSize.x, log.logSize.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void FlyCollisions(Frog& frog, Fly& fly, int& fliesPickedUp, float& timer, Sound frogPickUpFly)
	{
		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, fly.flyPosition.x, fly.flyPosition.y, fly.flySize.x, fly.flySize.y))
		{
			TpBackToStart(frog);

			timer = 30.0f;

			fly.isFlyPicked = true;

			fliesPickedUp++;

			//Pick up Fly Sound
			PlaySound(frogPickUpFly);

			SetSoundVolume(frogPickUpFly, 1);
		}
	}

	void CheckPlayerInput(Frog& frog, Sound frogJump)
	{
		if (IsKeyPressed(KEY_UP))
		{
			if (frog.frogPosition.y >= 64)
			{
				frog.frogPosition.y -= 64;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, 0.5f);
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			if (frog.frogPosition.y <= 959)
			{
				frog.frogPosition.y += 64;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, 0.5f);
		}

		if (IsKeyPressed(KEY_RIGHT))
		{
			if (frog.frogPosition.x <= 933)
			{
				frog.frogPosition.x += 64;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, 0.5f);
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			if (frog.frogPosition.x >= 39)
			{
				frog.frogPosition.x -= 64;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, 0.5f);
		}
	}

	void ResetGame(Frog& frog, Fly& fly, float& timer, int& fliesPickedUp)
	{
		frog.frogLives = 5;
		frog.frogPosition.x = 486;
		frog.frogPosition.y = 967.5f;

		fly.isFlyPicked = false;
		
		fliesPickedUp = 0;

		timer = 30.0f;
	}

	void UnloadDataPlay(Texture2D mouse, Texture2D bg, Frog frog, Log totalLogs[], LandEnemy landEnemies[], Fly flies[], Font gameFont, Sound frogJump, Sound frogSplat, Sound frogDrown, Sound frogPickUpFly, Sound frogRibbitClick, Music bgMusic)
	{
		UnloadTexture(mouse);

		UnloadTexture(bg);

		UnloadTexture(frog.frogTexture);

		for (int i = 0; i < LOG_COUNT; i++)
		{
			UnloadTexture(totalLogs[i].logTexture);
		}

		for (int i = 0; i < LAND_ENEMIES_COUNT; i++)
		{
			UnloadTexture(landEnemies[i].landEnemyTexture);
		}

		for (int i = 0; i < FLIES_COUNT; i++)
		{
			UnloadTexture(flies[i].flyTexture);
		}

		UnloadFont(gameFont);

		UnloadSound(frogJump);

		UnloadSound(frogSplat);
		
		UnloadSound(frogDrown);
		
		UnloadSound(frogPickUpFly);

		UnloadSound(frogRibbitClick);

		UnloadMusicStream(bgMusic);
	}
}
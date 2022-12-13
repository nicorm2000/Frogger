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
	static Vector2 mousePosition = GetMousePosition();

	static float timer = 30.0f;

	static Frog frog;

	static Fly flies[FLIES_COUNT];

	static int fliesPickedUp = 0;

	static void Initialize();

	static void Close();

	static void LogTp(Log& log);

	static void LandEnemyTp(LandEnemy& landEnemy);

	static void CheckPlayerInput(Sound frogJump);

	static bool CollisionRectangleRectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);

	static void LandGameCollisions(LandEnemy landEnemy, Sound frogSplat);

	static void WaterGameCollisions(Water water, Log totalLogs[], Sound frogDrown);

	static bool LogCollisions(Log log);

	static void FlyCollisions(Fly& fly, Sound frogPickUpFly);

	static void Respawn();

	static void TpBackToStart();

	static void UnloadDataPlay(Texture2D mouse, Texture2D bg, Log totalLogs[], LandEnemy landEnemies[], Font gameFont, Sound frogJump, Sound frogSplat, Sound frogDrown, Sound frogPickUpFly, Sound frogRibbitClick, Music bgMusic);

	static void WinAndLoseLogic(Sound frogRibbitClick, GameState& gameState);

	static void PauseLogic(bool& exitWindow, bool& isPaused, GameState& gameState, Sound frogRibbitClick);
	
	void ResetGame();

	void Game()
	{
		Initialize();
		HideCursor();
		SetExitKey(KEY_NULL);

		bool playingGame = true;
		bool isPaused = false;
		bool exitWindow = false;
		bool gameFinished = false;

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

		Water water;

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
			CreateFly(flies[i], static_cast<float>(FIRST_FLY_POS_X + currentDistance));

			currentDistance += SPACE_BETWEEN_FLIES;
		}

		//Logs
		{
			float smallLogPosY = 66;
			float mediumLogPosY = 130;
			float bigLogPosY = 194;

			for (int i = 0; i < SMALL_LOG_COUNT; i++)
			{
				smallLog[i] = CreateLog(Logs::Small, static_cast<float>(i * -LOG_DISTANCE));

				totalLogs[auxLogCount] = smallLog[i];
				auxLogCount++;
			}

			for (int i = 0; i < SMALL_LOG_COUNT2; i++)
			{
				smallLog2[i] = CreateLog(Logs::Small, static_cast<float>(i * LOG_DISTANCE));
				smallLog2[i].logPosition.y = smallLogPosY;
				smallLog2[i].logSpeed *= -1;

				totalLogs[auxLogCount] = smallLog2[i];
				auxLogCount++;
			}

			for (int i = 0; i < MEDIUM_LOG_COUNT; i++)
			{
				mediumLog[i] = CreateLog(Logs::Medium, static_cast<float>(i * LOG_DISTANCE));

				totalLogs[auxLogCount] = mediumLog[i];
				auxLogCount++;
			}

			for (int i = 0; i < MEDIUM_LOG_COUNT2; i++)
			{
				mediumLog2[i] = CreateLog(Logs::Medium, static_cast<float>(i * -LOG_DISTANCE));
				mediumLog2[i].logPosition.y = mediumLogPosY;
				mediumLog2[i].logSpeed *= -1;

				totalLogs[auxLogCount] = mediumLog2[i];
				auxLogCount++;
			}

			for (int i = 0; i < BIG_LOG_COUNT; i++)
			{
				bigLog[i] = CreateLog(Logs::Big, static_cast<float>(i * -LOG_DISTANCE));

				totalLogs[auxLogCount] = bigLog[i];
				auxLogCount++;
			}

			for (int i = 0; i < BIG_LOG_COUNT2; i++)
			{
				bigLog2[i] = CreateLog(Logs::Big, static_cast<float>(i * LOG_DISTANCE));
				bigLog2[i].logPosition.y = bigLogPosY;
				bigLog2[i].logSpeed *= -1;

				totalLogs[auxLogCount] = bigLog2[i];
				auxLogCount++;
			}
		}

		//Land Enemies
		{
			float truckDistance = 100;

			for (int i = 0; i < MOTORCYCLE_COUNT; i++)
			{
				motorcycle[i] = CreateVehicle(Vehicles::Motorcycle, static_cast<float>(i * -LAND_ENEMIES_DISTANCE));

				landEnemies[auxEnemyCount] = motorcycle[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < CAR_COUNT; i++)
			{
				car[i] = CreateVehicle(Vehicles::Car, static_cast<float>(i * -LAND_ENEMIES_DISTANCE));

				landEnemies[auxEnemyCount] = car[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < FAST_CAR_COUNT; i++)
			{
				fastCar[i] = CreateVehicle(Vehicles::FastCar, static_cast<float>(i * -LAND_ENEMIES_DISTANCE));

				landEnemies[auxEnemyCount] = fastCar[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < VAN_COUNT; i++)
			{
				van[i] = CreateVehicle(Vehicles::Van, static_cast<float>(i * -LAND_ENEMIES_DISTANCE));

				landEnemies[auxEnemyCount] = van[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < BUS_COUNT; i++)
			{
				bus[i] = CreateVehicle(Vehicles::Bus, static_cast<float>(i * -LAND_ENEMIES_DISTANCE));

				landEnemies[auxEnemyCount] = bus[i];
				auxEnemyCount++;
			}

			for (int i = 0; i < TRUCK_COUNT; i++)
			{
				truck[i] = CreateVehicle(Vehicles::Truck, static_cast<float>(i * (-LAND_ENEMIES_DISTANCE + truckDistance)));

				landEnemies[auxEnemyCount] = truck[i];
				auxEnemyCount++;
			}
		}
		
		PlayMusicStream(bgMusic);

		SetMusicVolume(bgMusic, 0.25f);

		while (playingGame && !WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(WHITE);

			UpdateMusicStream(bgMusic);

			mousePosition = GetMousePosition();

			switch (gameState)
			{
				case game::GameState::GAMETITLE:

					////Logic

					MainMenuLogic(mousePosition, gameState, frogRibbitClick);

					////Draw

					MainMenuDraw();

					break;

				case game::GameState::GAME:
					
					////Logic

					if (fliesPickedUp != 5)
					{
						if (!isPaused)
						{
							if (frog.isAlive)
							{
								timer -= GetFrameTime();

								if (timer <= 0.0f)
								{
									Respawn();
								}

								CheckPlayerInput(frogJump);

								for (int i = 0; i < LAND_ENEMIES_COUNT; i++)
								{
									LandGameCollisions(landEnemies[i], frogSplat);
								}

								WaterGameCollisions(water, totalLogs, frogDrown);

								for (int i = 0; i < FLIES_COUNT; i++)
								{
									if (!flies[i].isFlyPicked)
									{
										FlyCollisions(flies[i], frogPickUpFly);
									}
								}

								if (IsKeyPressed(KEY_ESCAPE) && !gameFinished)
								{
									PlaySound(frogRibbitClick);

									SetSoundVolume(frogRibbitClick, 1);

									isPaused = true;
									exitWindow = true;
								}
							}
							else
							{
								WinAndLoseLogic(frogRibbitClick, gameState);
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
						WinAndLoseLogic(frogRibbitClick, gameState);
					}

					//Pause Logic

					PauseLogic(exitWindow, isPaused, gameState, frogRibbitClick);

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
						DrawWinMenu(gameFont);
					}

					if (fliesPickedUp != 5 && !frog.isAlive)
					{
						DrawLoseMenu(gameFont);
					}

					break;

				case game::GameState::HOWTOPLAY:
					
					////Logic

					HowToPlayLogic(mousePosition, gameState, frogRibbitClick);

					////Draw

					HowToPlayDraw();

					break;

				case game::GameState::CREDITS:
					
					////Logic
					
					CreditsLogic(mousePosition, gameState, frogRibbitClick);

					////Draw

					CreditsDraw();

					break;

				case game::GameState::EXIT:

					UnloadDataMainMenu(frogRibbitClick);
					UnloadDataPlay(mouse, bg, totalLogs, landEnemies, gameFont, frogJump, frogSplat, frogDrown, frogPickUpFly, frogRibbitClick, bgMusic);
					UnloadDataHowToPlay(frogRibbitClick);
					UnloadDataCredits(frogRibbitClick);
					
					playingGame = false;

					break;
			}

			//Mouse Draw
			DrawTexture(mouse, static_cast<int>(mousePosition.x - mouse.width / 2), static_cast<int>(mousePosition.y - mouse.height / 2), WHITE);

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
	
	void WinAndLoseLogic(Sound frogRibbitClick, GameState& gameState)
	{
		if (CheckCollisionPointRec(mousePosition, { 350, 525, 150, 100 }))
		{
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::GAMETITLE;
			}
		}
		if (CheckCollisionPointRec(mousePosition, { 530, 525, 150, 100 }))
		{
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::EXIT;
			}
		}
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

	void DrawLoseMenu(Font gameFont)
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

	void PauseLogic(bool& exitWindow, bool& isPaused, GameState& gameState,Sound frogRibbitClick)
	{
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

	void Respawn()
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

	void TpBackToStart()
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

	void LandGameCollisions(LandEnemy landEnemy, Sound frogSplat)
	{
		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, landEnemy.landEnemyPosition.x, landEnemy.landEnemyPosition.y, landEnemy.landEnemySize.x, landEnemy.landEnemySize.y))
		{
			Respawn();

			//Splat Sound
			PlaySound(frogSplat);

			SetSoundVolume(frogSplat, 1);
		}
	}

	void WaterGameCollisions(Water water, Log totalLogs[], Sound frogDrown)
	{
		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, water.waterPosition.x, water.waterPosition.y, water.waterSize.x, water.waterSize.y))
		{
			bool frogOnLog = false;

			for (int i = 0; i < LOG_COUNT; i++)
			{
				frogOnLog = LogCollisions(totalLogs[i]);

				if (frogOnLog)
				{
					break;
				}
			}

			if (!frogOnLog)
			{
				Respawn();

				//Drown Sound
				PlaySound(frogDrown);

				SetSoundVolume(frogDrown, 1);
			}
		}
	}

	bool LogCollisions(Log log)
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

	void FlyCollisions(Fly& fly, Sound frogPickUpFly)
	{
		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, fly.flyPosition.x, fly.flyPosition.y, fly.flySize.x, fly.flySize.y))
		{
			TpBackToStart();

			timer = 30.0f;

			fly.isFlyPicked = true;

			fliesPickedUp++;

			//Pick up Fly Sound
			PlaySound(frogPickUpFly);

			SetSoundVolume(frogPickUpFly, 1);
		}
	}

	void CheckPlayerInput(Sound frogJump)
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

	void ResetGame()
	{
		frog.frogLives = 5;
		frog.frogPosition.x = 486;
		frog.frogPosition.y = 967.5f;
		
		for (int i = 0; i < FLIES_COUNT; i++)
		{
			flies[i].isFlyPicked = false;
		}
		
		fliesPickedUp = 0;

		timer = 30.0f;
	}

	void UnloadDataPlay(Texture2D mouse, Texture2D bg, Log totalLogs[], LandEnemy landEnemies[], Font gameFont, Sound frogJump, Sound frogSplat, Sound frogDrown, Sound frogPickUpFly, Sound frogRibbitClick, Music bgMusic)
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
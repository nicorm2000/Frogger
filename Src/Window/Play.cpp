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
		if (CheckCollisionPointRec(mousePosition, { LEFT_BUTTON_POSITION_X, BUTTON_POSITION_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y }))
		{
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				PlaySound(frogRibbitClick);

				SetSoundVolume(frogRibbitClick, 1);

				gameState = GameState::GAMETITLE;
			}
		}
		if (CheckCollisionPointRec(mousePosition, { RIGHT_BUTTON_POSITION_X, BUTTON_POSITION_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y }))
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
		float fontSizeTitle = 90;
		float fontSizeButttons = 80;
		float title1X = static_cast<float>(GetScreenWidth() - 730);
		float title1Y = static_cast<float>((GetScreenHeight() / 2) - 150);
		float title2X = static_cast<float>(GetScreenWidth() - 700);
		float title2Y = static_cast<float>((GetScreenHeight() / 2) - 80);
		float yesPosX = 375;
		float noPosX = 570;
		float posY = 540;

		DrawRectangleRounded({ OUTSIDE_BORDER_POSITION_X, OUTSIDE_BORDER_POSITION_Y, OUTSIDE_BORDER_SIZE_X, OUTSIDE_BORDER_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_POSITION_X, INSIDE_BORDER_POSITION_Y, INSIDE_BORDER_SIZE_X, INSIDE_BORDER_SIZE_Y }, ROUNDNESS, SEGMENTS, LIGHTGRAY);

		DrawTextPro(gameFont, "Do you want to", { title1X, title1Y }, { 0, 0 }, 0, fontSizeTitle, 0, BLACK);
		DrawTextPro(gameFont, "keep playing?", { title2X, title2Y }, { 0, 0 }, 0, fontSizeTitle, 0, BLACK);

		DrawRectangleRounded({ OUTSIDE_BORDER_LEFT_BUTTON_POSITION_X, OUTSIDE_BORDER_LEFT_BUTTON_POSITION_Y, OUTSIDE_BORDER_LEFT_BUTTON_SIZE_X, OUTSIDE_BORDER_LEFT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_LEFT_BUTTON_POSITION_X, INSIDE_BORDER_LEFT_BUTTON_POSITION_Y, INSIDE_BORDER_LEFT_BUTTON_SIZE_X, INSIDE_BORDER_LEFT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, GREEN);

		DrawTextPro(gameFont, "YES", { yesPosX, posY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);

		DrawRectangleRounded({ OUTSIDE_BORDER_RIGHT_BUTTON_POSITION_X, OUTSIDE_BORDER_RIGHT_BUTTON_POSITION_Y, OUTSIDE_BORDER_RIGHT_BUTTON_SIZE_X, OUTSIDE_BORDER_RIGHT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_RIGHT_BUTTON_POSITION_X, INSIDE_BORDER_RIGHT_BUTTON_POSITION_Y, INSIDE_BORDER_RIGHT_BUTTON_SIZE_X, INSIDE_BORDER_RIGHT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, RED);

		DrawTextPro(gameFont, "NO", { noPosX, posY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);
	}

	void DrawWinMenu(Font gameFont)
	{
		float fontSizeTitle = 150;
		float fontSizeButttons = 50;
		float titleX = static_cast<float>(GetScreenWidth() - 730);
		float titleY = static_cast<float>((GetScreenHeight() / 2) - 150);
		float leftButtonPosX = 365;
		float leftButton2PosX = 350;
		float leftButtonPosY = 530;
		float leftButton2PosY = 565;
		float rightButtonPosX = 575;
		float rightButtonPosY = 530;
		float rightButton2PosX = 560;
		float rightButton2PosY = 565;

		DrawRectangleRounded({ OUTSIDE_BORDER_POSITION_X, OUTSIDE_BORDER_POSITION_Y, OUTSIDE_BORDER_SIZE_X, OUTSIDE_BORDER_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_POSITION_X, INSIDE_BORDER_POSITION_Y, INSIDE_BORDER_SIZE_X, INSIDE_BORDER_SIZE_Y }, ROUNDNESS, SEGMENTS, LIGHTGRAY);

		DrawTextPro(gameFont, "You Won!", { titleX, titleY }, { 0, 0 }, 0, fontSizeTitle, 0, BLACK);

		DrawRectangleRounded({ OUTSIDE_BORDER_LEFT_BUTTON_POSITION_X, OUTSIDE_BORDER_LEFT_BUTTON_POSITION_Y, OUTSIDE_BORDER_LEFT_BUTTON_SIZE_X, OUTSIDE_BORDER_LEFT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_LEFT_BUTTON_POSITION_X, INSIDE_BORDER_LEFT_BUTTON_POSITION_Y, INSIDE_BORDER_LEFT_BUTTON_SIZE_X, INSIDE_BORDER_LEFT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, GREEN);

		DrawTextPro(gameFont, "go back", { leftButtonPosX, leftButtonPosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);
		DrawTextPro(gameFont, "to menu", { leftButton2PosX, leftButton2PosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);

		DrawRectangleRounded({ OUTSIDE_BORDER_RIGHT_BUTTON_POSITION_X, OUTSIDE_BORDER_RIGHT_BUTTON_POSITION_Y, OUTSIDE_BORDER_RIGHT_BUTTON_SIZE_X, OUTSIDE_BORDER_RIGHT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_RIGHT_BUTTON_POSITION_X, INSIDE_BORDER_RIGHT_BUTTON_POSITION_Y, INSIDE_BORDER_RIGHT_BUTTON_SIZE_X, INSIDE_BORDER_RIGHT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, RED);

		DrawTextPro(gameFont, "exit", { rightButtonPosX, rightButtonPosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);
		DrawTextPro(gameFont, "game", { rightButton2PosX, rightButton2PosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);
	}

	void DrawLoseMenu(Font gameFont)
	{
		float fontSizeTitle = 100;
		float fontSizeTitle2 = 90;
		float fontSizeButttons = 50;
		float titleX = static_cast<float>(GetScreenWidth() - 650);
		float titleY = static_cast<float>((GetScreenHeight() / 2) - 180);
		float subtitleX1 = static_cast<float>(GetScreenWidth() - 725);
		float subtitleX2 = static_cast<float>(GetScreenWidth() - 475);
		float subtitleX3 = static_cast<float>(GetScreenWidth() - 415);
		float subtitleY = static_cast<float>((GetScreenHeight() / 2) - 80);
		float leftButtonPosX = 365;
		float leftButton2PosX = 350;
		float leftButtonPosY = 530;
		float leftButton2PosY = 565;
		float rightButtonPosX = 575;
		float rightButtonPosY = 530;
		float rightButton2PosX = 560;
		float rightButton2PosY = 565;

		DrawRectangleRounded({ OUTSIDE_BORDER_POSITION_X, OUTSIDE_BORDER_POSITION_Y, OUTSIDE_BORDER_SIZE_X, OUTSIDE_BORDER_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_POSITION_X, INSIDE_BORDER_POSITION_Y, INSIDE_BORDER_SIZE_X, INSIDE_BORDER_SIZE_Y }, ROUNDNESS, SEGMENTS, LIGHTGRAY);

		DrawTextPro(gameFont, "You Lost!", { titleX, titleY }, { 0, 0 }, 0, fontSizeTitle, 0, BLACK);
		DrawTextPro(gameFont, "You got", { subtitleX1, subtitleY }, { 0, 0 }, 0, fontSizeTitle2, 0, BLACK);
		DrawTextPro(gameFont, TextFormat("%i", fliesPickedUp), { subtitleX2, subtitleY }, { 0, 0 }, 0, fontSizeTitle2, 0, WHITE);
		DrawTextPro(gameFont, "flies", { subtitleX3, subtitleY }, { 0, 0 }, 0, fontSizeTitle2, 0, BLACK);

		DrawRectangleRounded({ OUTSIDE_BORDER_LEFT_BUTTON_POSITION_X, OUTSIDE_BORDER_LEFT_BUTTON_POSITION_Y, OUTSIDE_BORDER_LEFT_BUTTON_SIZE_X, OUTSIDE_BORDER_LEFT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_LEFT_BUTTON_POSITION_X, INSIDE_BORDER_LEFT_BUTTON_POSITION_Y, INSIDE_BORDER_LEFT_BUTTON_SIZE_X, INSIDE_BORDER_LEFT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, GREEN);

		DrawTextPro(gameFont, "go back", { leftButtonPosX, leftButtonPosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);
		DrawTextPro(gameFont, "to menu", { leftButton2PosX, leftButton2PosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);

		DrawRectangleRounded({ OUTSIDE_BORDER_RIGHT_BUTTON_POSITION_X, OUTSIDE_BORDER_RIGHT_BUTTON_POSITION_Y, OUTSIDE_BORDER_RIGHT_BUTTON_SIZE_X, OUTSIDE_BORDER_RIGHT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, BLACK);
		DrawRectangleRounded({ INSIDE_BORDER_RIGHT_BUTTON_POSITION_X, INSIDE_BORDER_RIGHT_BUTTON_POSITION_Y, INSIDE_BORDER_RIGHT_BUTTON_SIZE_X, INSIDE_BORDER_RIGHT_BUTTON_SIZE_Y }, ROUNDNESS, SEGMENTS, RED);

		DrawTextPro(gameFont, "exit", { rightButtonPosX, rightButtonPosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);
		DrawTextPro(gameFont, "game", { rightButton2PosX, rightButton2PosY }, { 0, 0 }, 0, fontSizeButttons, 0, BLACK);
	}

	void PauseLogic(bool& exitWindow, bool& isPaused, GameState& gameState,Sound frogRibbitClick)
	{
		if (exitWindow)
		{
			if (CheckCollisionPointRec(mousePosition, { LEFT_BUTTON_POSITION_X, BUTTON_POSITION_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y }))
			{
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					PlaySound(frogRibbitClick);

					SetSoundVolume(frogRibbitClick, 1);

					exitWindow = false;
					isPaused = !isPaused;
				}
			}
			if (CheckCollisionPointRec(mousePosition, { RIGHT_BUTTON_POSITION_X, BUTTON_POSITION_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y }))
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
		float spawnTp = 310;
		float firstTpPosition = 50;
		float secondTpPosition = 200;

		if (log.logSpeed < 0)
		{
			if (log.logPosition.x < -spawnTp)
			{
				log.logPosition.x = static_cast<float>(GetScreenWidth()) + firstTpPosition;
			}
		}
		else
		{
			if (log.logPosition.x > GetScreenWidth() + secondTpPosition)
			{
				log.logPosition.x = -spawnTp;
			}
		}
	}

	void LandEnemyTp(LandEnemy& landEnemy)
	{
		float firstTpPosition = 200;
		float secondTpPosition = 50;

		if (landEnemy.landEnemySpeed < 0)
		{
			if (landEnemy.landEnemyPosition.x < -firstTpPosition)
			{
				landEnemy.landEnemyPosition.x = static_cast<float>(GetScreenWidth()) + secondTpPosition;
			}
		}
		else
		{
			if (landEnemy.landEnemyPosition.x > GetScreenWidth() + firstTpPosition)
			{
				landEnemy.landEnemyPosition.x = -firstTpPosition;
			}
		}
	}

	void Respawn()
	{
		timer = TIMER;

		frog.frogLives--;

		frog.frogPosition.x = FROG_INITIAL_POSITION_X;
		frog.frogPosition.y = FROG_INITIAL_POSITION_Y;

		if (frog.frogLives <= 0)
		{
			frog.isAlive = false;
		}
	}

	void TpBackToStart()
	{
		frog.frogPosition.x = FROG_INITIAL_POSITION_X;
		frog.frogPosition.y = FROG_INITIAL_POSITION_Y;
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
		float splatSFX = 1;

		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, landEnemy.landEnemyPosition.x, landEnemy.landEnemyPosition.y, landEnemy.landEnemySize.x, landEnemy.landEnemySize.y))
		{
			Respawn();

			//Splat Sound
			PlaySound(frogSplat);

			SetSoundVolume(frogSplat, splatSFX);
		}
	}

	void WaterGameCollisions(Water water, Log totalLogs[], Sound frogDrown)
	{
		float drownSFX = 1;

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

				SetSoundVolume(frogDrown, drownSFX);
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
		float pickUpFlySFX = 1;

		if (CollisionRectangleRectangle(frog.frogPosition.x, frog.frogPosition.y, frog.frogSize.x, frog.frogSize.y, fly.flyPosition.x, fly.flyPosition.y, fly.flySize.x, fly.flySize.y))
		{
			TpBackToStart();

			timer = TIMER;

			fly.isFlyPicked = true;

			fliesPickedUp++;

			//Pick up Fly Sound
			PlaySound(frogPickUpFly);

			SetSoundVolume(frogPickUpFly, pickUpFlySFX);
		}
	}

	void CheckPlayerInput(Sound frogJump)
	{
		int topLimit = 64;
		int bottomLimit = 959;
		int rightLimit = 933;
		int leftLimit = 39;

		float jumpSFX = 0.5f;

		if (IsKeyPressed(KEY_UP))
		{
			if (frog.frogPosition.y >= topLimit)
			{
				frog.frogPosition.y -= CELL_SIZE;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, jumpSFX);
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			if (frog.frogPosition.y <= bottomLimit)
			{
				frog.frogPosition.y += CELL_SIZE;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, jumpSFX);
		}

		if (IsKeyPressed(KEY_RIGHT))
		{
			if (frog.frogPosition.x <= rightLimit)
			{
				frog.frogPosition.x += CELL_SIZE;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, jumpSFX);
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			if (frog.frogPosition.x >= leftLimit)
			{
				frog.frogPosition.x -= CELL_SIZE;
			}

			//Jump Sound
			PlaySound(frogJump);

			SetSoundVolume(frogJump, jumpSFX);
		}
	}

	void ResetGame()
	{
		frog.isAlive = true;
		frog.frogLives = FROG_LIVES;
		frog.frogPosition.x = FROG_INITIAL_POSITION_X;
		frog.frogPosition.y = FROG_INITIAL_POSITION_Y;
		
		for (int i = 0; i < FLIES_COUNT; i++)
		{
			flies[i].isFlyPicked = false;
		}
		
		fliesPickedUp = 0;

		timer = TIMER;
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
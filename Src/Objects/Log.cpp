#include "Log.h"

#include "raylib.h"

namespace game
{
	Log CreateLog(Logs logs, float distance)
	{
		Log log;

		switch (logs)
		{
			case game::Logs::Small:

				log.logPosition.x = -200 + distance;
				log.logPosition.y = 258;
				log.logSize.x = 180;
				log.logSize.y = 60;
				log.logSpeed = 200;
				log.logColor = WHITE;
				log.logTexture = LoadTexture("Resources/Textures/logSmall.png");

				break;

			case game::Logs::Medium:

				log.logPosition.x = 1124 + distance;
				log.logPosition.y = 322;
				log.logSize.x = 240;
				log.logSize.y = 60;
				log.logSpeed = -175;
				log.logColor = WHITE;
				log.logTexture = LoadTexture("Resources/Textures/logMedium.png");

				break;

			case game::Logs::Big:

				log.logPosition.x = -310 + distance;
				log.logPosition.y = 386;
				log.logSize.x = 300;
				log.logSize.y = 60;
				log.logSpeed = 150;
				log.logColor = WHITE;
				log.logTexture = LoadTexture("Resources/Textures/logBig.png");

				break;

			default:

				log = CreateLog(Logs::Small, distance);//The function is called again so there is always an object called

				break;
		}

		log.logType = logs;

		return log;
	}

	void DrawLog(Log log)
	{
		//DrawRectangle(static_cast<int>(log.logPosition.x), static_cast<int>(log.logPosition.y), static_cast<int>(log.logSize.x), static_cast<int>(log.logSize.y), log.logColor);
		DrawTexture(log.logTexture, static_cast<int>(log.logPosition.x), static_cast<int>(log.logPosition.y), log.logColor);
	}
}
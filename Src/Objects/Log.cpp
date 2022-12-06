#include "Log.h"

namespace game
{
	Log CreateSmallLog(Log& log)
	{
		log.logPosition.x = -200;
		log.logPosition.y = 258;
		log.logSize.x = 180;
		log.logSize.y = 60;
		log.logSpeed = 200;
		log.logColor = BROWN;

		return log;
	}

	Log CreateMediumLog(Log& log)
	{
		log.logPosition.x = 1124;
		log.logPosition.y = 322;
		log.logSize.x = 240;
		log.logSize.y = 60;
		log.logSpeed = -175;
		log.logColor = BROWN;

		return log;
	}

	Log CreateBigLog(Log& log)
	{
		log.logPosition.x = -310;
		log.logPosition.y = 386;
		log.logSize.x = 300;
		log.logSize.y = 60;
		log.logSpeed = 150;
		log.logColor = BROWN;

		return log;
	}

	void DrawLog(Log log)
	{
		DrawRectangle(static_cast<int>(log.logPosition.x), static_cast<int>(log.logPosition.y), static_cast<int>(log.logSize.x), static_cast<int>(log.logSize.y), log.logColor);
	}
}
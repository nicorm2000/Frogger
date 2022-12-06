#include "Log.h"

namespace game
{
	Log CreateSmallLog(Log& log)
	{
		log.logPosition.x = -150;
		log.logPosition.y = 256;
		log.logSize.x = 180;
		log.logSize.y = 60;
		log.logSpeed = 250;
		log.logColor = BROWN;

		return log;
	}

	Log CreateMediumLog(Log& log)
	{
		log.logPosition.x = 1124;
		log.logPosition.y = 320;
		log.logSize.x = 240;
		log.logSize.y = 60;
		log.logSpeed = 250;
		log.logColor = BROWN;

		return log;
	}

	Log CreateBigLog(Log& log)
	{
		log.logPosition.x = -150;
		log.logPosition.y = 384;
		log.logSize.x = 300;
		log.logSize.y = 60;
		log.logSpeed = 250;
		log.logColor = BROWN;

		return log;
	}

	void DrawLog(Log log)
	{
		DrawRectangle(static_cast<int>(log.logPosition.x), static_cast<int>(log.logPosition.y), static_cast<int>(log.logSize.x), static_cast<int>(log.logSize.y), log.logColor);
	}
}
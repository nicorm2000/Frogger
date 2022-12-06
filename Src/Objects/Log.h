#pragma once

#include "raylib.h"

namespace game
{
	struct Log
	{
		Vector2 logPosition{};
		Vector2 logSize;
		float logSpeed;
		bool isFrogOnLog;
		Color logColor;
		Texture logTexture;
	};

	Log CreateSmallLog(Log& log);
	
	Log CreateMediumLog(Log& log);
	
	Log CreateBigLog(Log& log);

	void DrawLog(Log log);
}
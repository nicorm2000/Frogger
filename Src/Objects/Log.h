#pragma once

#include "raylib.h"

namespace game
{
	const int SMALL_LOG_COUNT = 3;
	const int MEDIUM_LOG_COUNT = 3;
	const int BIG_LOG_COUNT = 3;

	enum class Logs
	{
		Small = 0,
		Medium,
		Big
	};

	struct Log
	{
		Vector2 logPosition{};
		Vector2 logSize;
		float logSpeed;
		bool isFrogOnLog;
		Color logColor;
		Texture logTexture;
	};

	Log CreateLog(Logs logs, float distance);

	void DrawLog(Log log);
}
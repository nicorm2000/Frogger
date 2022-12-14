#pragma once

#include "raylib.h"

namespace game
{
	void HowToPlayLoad();

	void HowToPlayLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick);

	void HowToPlayDraw(Texture howToPlayScene);
	
	void UnloadDataHowToPlay(Texture howToPlayScene);
}
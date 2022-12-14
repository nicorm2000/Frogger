#pragma once
#include "Window/HowToPlay.h"

#include "raylib.h"

namespace game
{
	void HowToPlayLoad();

	void HowToPlayLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick);

	void HowToPlayDraw(Texture howToPlayScene);
	
	void UnloadDataHowToPlay(Sound frogRibbitClick, Texture howToPlayScene);
}
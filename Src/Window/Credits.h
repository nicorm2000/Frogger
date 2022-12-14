#pragma once
#include "Window/MainMenu.h"

#include "raylib.h"

namespace game
{
	const int EXIT_BUTTON_POSITION_X = 10;

	const int EXIT_BUTTON_POSITION_Y = 10;
	
	const int EXIT_BUTTON_SIZE_X = 45;
	
	const int EXIT_BUTTON_SIZE_Y = 45;

	void CreditsLoad();

	void CreditsLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick);

	void CreditsDraw(Texture creditsScene);

	void UnloadDataCredits(Sound frogRibbitClick, Texture creditsScene);
}
#pragma once
#include "Window/MainMenu.h"

#include "raylib.h"

namespace game
{
	const int CREDITS_BUTTON_SIZE_Y = 70;

	void CreditsLoad();

	void CreditsLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick);

	void CreditsDraw(Texture creditsScene);

	void UnloadDataCredits(Sound frogRibbitClick, Texture creditsScene);
}
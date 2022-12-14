#pragma once
#include "Window/MainMenu.h"

#include "raylib.h"

namespace game
{
	void CreditsLoad();

	void CreditsLogic(Vector2 mousePosition, GameState& gameState, Sound frogRibbitClick);

	void CreditsDraw(Texture creditsScene);

	void UnloadDataCredits(Sound frogRibbitClick, Texture creditsScene);
}
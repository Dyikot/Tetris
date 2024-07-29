#pragma once

#include "Scene.h"
#include "GameScene.h"
#include "../Application/Application.h"
#include "..\Objects\Controls\Button.h"
#include "..\Objects\Controls\TextBlock.h"

class GameOverMenu: public Scene
{
private:
	TextBlock _gameOverTextBlock = TextBlock(
		/*postion*/{ .x = 80, .y = 160 },
		/*width*/ 240,
		/*height*/ 80,
		/*background*/ Colors::None,
		/*text*/ "Game over",
		/*textColor*/ Colors::Red,
		/*textFont*/ TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 96)
	);

	Button _retryButton = Button(
		/*postion*/{ .x = 140, .y = 300 },
		/*width*/ 120,
		/*height*/ 40,
		/*background*/ Colors::None,
		/*borderColor*/ Colors::Green,
		/*text*/ "  Retry  ",
		/*textColor*/ Colors::White,
		/*textFont*/ TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 32)
	);	

	Button _exitButton = Button(
		/*postion*/{ .x = 140, .y = 350 },
		/*width*/ 120,
		/*height*/ 40,
		/*background*/ Colors::None,
		/*borderColor*/ Colors::Green,
		/*text*/ "   Exit   ",
		/*textColor*/ Colors::White,
		/*textFont*/ TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 32)
	);	
public:
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
};
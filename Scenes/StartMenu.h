#pragma once

#include "Scene.h"
#include "GameScene.h"
#include "..\Application\Application.h"
#include "..\Objects\Controls\Button.h"
#include "..\Objects\Controls\TextBlock.h"

class StartMenu : public Scene
{
private:
	TextBlock _title = TextBlock(
		/*postion*/{ .x = 80, .y = 160 },
		/*width*/ 240,
		/*height*/ 80,
		/*background*/ Colors::None,
		/*text*/ "Tetris",
		/*textColor*/ Colors::White,
		/*textFont*/ TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 96)
	);
	Button _startGameButton = Button(
		/*postion*/{ .x = 140, .y = 300 },
		/*width*/ 120,
		/*height*/ 40,
		/*background*/ Colors::None,
		/*borderColor*/ Colors::Green,
		/*text*/ "  Play  ",
		/*textColor*/ Colors::White,
		/*textFont*/ TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 32)
	);
	Button _settingsButton = Button(
		/*postion*/{ .x = 140, .y = 350 },
		/*width*/ 120,
		/*height*/ 40,
		/*background*/ Colors::None,
		/*borderColor*/ Colors::Green,
		/*text*/ "Settings",
		/*textColor*/ Colors::Grey,
		/*textFont*/ TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 32)
	);
	Button _exitButton = Button(
		/*postion*/{ .x = 140, .y = 400 },
		/*width*/ 120,
		/*height*/ 40,
		/*background*/ Colors::None,
		/*borderColor*/ Colors::Green,
		/*text*/ "  Exit  ",
		/*textColor*/ Colors::White,
		/*textFont*/ TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 32)
	);
public:
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
};
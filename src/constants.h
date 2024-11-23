#pragma once
#include <raylib.h>
#include "scene/SceneID.h"


#define RES "./resources/"
#define IMAGES_PATH RES "images/"


namespace pz {

	constexpr int SCREEN_W{ 1280 };
	constexpr int SCREEN_H{ 720 };
	constexpr int FPS{ 60 };
	constexpr char WINDOW_TITLE[]{ "Puzzle Game" };
	
	constexpr Color BACKGROUND_COLOR{ 18, 18, 18 };
	constexpr pz::SceneID MAIN_SCENE{ pz::ChooseImageSceneID };
	constexpr int PUZZLE_RECT_SIZE{ 80 };
	constexpr float TIME_TO_MOVE_A_PUZZLE_RECT{ 0.20f };
	
	constexpr float SCROLL_SPEED{ 740.0f };

}
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

}
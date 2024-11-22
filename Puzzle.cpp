// Puzzle.cpp : Defines the entry point for the application.
//
#include "Puzzle.h"


int main() {
	InitWindow(pz::SCREEN_W, pz::SCREEN_H, pz::WINDOW_TITLE);
	SetTargetFPS(pz::FPS);

	pz::scene_manager_init();

	while (WindowShouldClose() == false) {
		pz::scene_manager_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(pz::BACKGROUND_COLOR);
		pz::scene_manager_draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

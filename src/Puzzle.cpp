#include "Puzzle.h"


void update_frame() {
	pz::scene_manager_update(GetFrameTime());
	BeginDrawing();
	ClearBackground(pz::BACKGROUND_COLOR);
	pz::scene_manager_draw();
	EndDrawing();
}


int main() {
	InitWindow(pz::SCREEN_W, pz::SCREEN_H, pz::WINDOW_TITLE);	

	pz::scene_manager_init();

	#if defined(PLATFORM_WEB)
    	emscripten_set_main_loop(UpdateDrawFrame, pz::FPS, 1);
	#else
    	SetTargetFPS(pz::FPS);
    	while (!WindowShouldClose()) {
        	update_frame();
    	}
	#endif	

	CloseWindow();
	return 0;
}

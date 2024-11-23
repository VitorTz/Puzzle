#include "Scene.h"


constexpr float PADDING = 20.0f;
constexpr float TOP_BAR_WIDTH = pz::SCREEN_W;
constexpr float TOP_BAR_HEIGHT = 80.0f;
constexpr Rectangle TOP_BAR_RECT{ 0.0f, 0.0f, TOP_BAR_WIDTH, TOP_BAR_HEIGHT };
constexpr Color TOP_BAR_COLOR{ 31, 32, 33, 255 };
constexpr Color TOP_BAR_LINE_COLOR{ WHITE };
constexpr float TOP_BAR_LINE_THICK{ 2.0f };
constexpr float IMAGE_MAX_WIDTH = pz::SCREEN_W;
constexpr float IMAGE_MAX_HEIGHT = pz::SCREEN_H - TOP_BAR_HEIGHT - PADDING * 2.0f;


static bool should_change_scene{};
static bool should_reset_puzzle{};


static void change_scene_aux() {
	should_change_scene = true;
}


static void reset_puzzle_aux() {
	should_reset_puzzle = true;
}


pz::PuzzleScene::PuzzleScene(

) : puzzle_grid(pz::globals::puzzle_image_path.c_str(), IMAGE_MAX_WIDTH, IMAGE_MAX_HEIGHT),
	return_button(RES "icons/back.png", RES "icons/back-hover.png", 0, 0, change_scene_aux),
	reset_button(RES "icons/reset.png", RES "icons/reset-hover.png", 0, 0, reset_puzzle_aux),
	preview_button(RES "icons/preview.png", RES "icons/preview-hover.png", 0, 0, NULL) {

	// Puzzle pos
	this->puzzle_grid.set_left(
		pz::SCREEN_W / 2.0f - this->puzzle_grid.width() / 2.0f
	);
	this->puzzle_grid.set_top(
		(IMAGE_MAX_HEIGHT / 2.0f + TOP_BAR_HEIGHT + PADDING) - this->puzzle_grid.height() / 2.0f
	);

	// BUTTONS
	this->return_button.set_right(pz::SCREEN_W - PADDING);
	this->return_button.set_centery(TOP_BAR_HEIGHT / 2.0f);
	
	this->reset_button.set_right(this->return_button.get_left() - PADDING);
	this->reset_button.set_centery(TOP_BAR_HEIGHT / 2.0f);
		
	this->preview_button.set_right(this->reset_button.get_left() - PADDING);
	this->preview_button.set_centery(TOP_BAR_HEIGHT / 2.0f);	
}	


void pz::PuzzleScene::update(const float dt) {
	if (should_change_scene) {
		should_change_scene = false;
		pz::scene_manager_change_scene(pz::ChooseImageSceneID);		
	}

	if (should_reset_puzzle) {
		should_reset_puzzle = false;
		this->puzzle_grid.reset();
	}

	this->return_button.update(dt);
	this->preview_button.update(dt);
	this->reset_button.update(dt);
	this->puzzle_grid.update(dt);
}


void pz::PuzzleScene::draw() {
	DrawRectangleRec(TOP_BAR_RECT, TOP_BAR_COLOR);
	DrawLineEx(
		Vector2{ 0.0f, TOP_BAR_HEIGHT }, 
		Vector2{ TOP_BAR_WIDTH, TOP_BAR_HEIGHT }, 
		TOP_BAR_LINE_THICK, 
		TOP_BAR_LINE_COLOR
	);
	
	this->return_button.draw();
	this->preview_button.draw();
	this->reset_button.draw();

	// Draw Complete image	
	if (this->preview_button.is_hovered()) {
		this->puzzle_grid.draw_preview();
		return;
	}
	// Draw puzzle	
	this->puzzle_grid.draw();
}
#include "Scene.h"
#include <algorithm>
#include <random>
#include <chrono>       

constexpr float PADDING = 20.0f;
constexpr float TOP_BAR_WIDTH = pz::SCREEN_W;
constexpr float TOP_BAR_HEIGHT = 80.0f;
constexpr Rectangle TOP_BAR_RECT{ 0.0f, 0.0f, TOP_BAR_WIDTH, TOP_BAR_HEIGHT };
constexpr Color TOP_BAR_COLOR{ 31, 32, 33, 255 };
constexpr Color TOP_BAR_LINE_COLOR{ WHITE };
constexpr float TOP_BAR_LINE_THICK{ 2.0f };
constexpr float IMAGE_MAX_WIDTH = pz::SCREEN_W;
constexpr float IMAGE_MAX_HEIGHT = pz::SCREEN_H - TOP_BAR_HEIGHT - PADDING * 2.0f;
constexpr int PUZZLE_RECT_SIZE{ 60 };



static Vector2 image_topleft{};
static int grid_rows{};
static int grid_cols{};
static bool should_change_scene{};
static bool should_reset_puzzle{};


static void change_scene_aux() {
	should_change_scene = true;
}


static void reset_puzzle_aux() {
	should_reset_puzzle = true;
}


pz::PuzzleScene::PuzzleScene(

) : return_button(RES "icons/back.png", RES "icons/back-hover.png", 0, 0, change_scene_aux),
	reset_button(RES "icons/reset.png", RES "icons/reset-hover.png", 0, 0, reset_puzzle_aux),
	preview_button(RES "icons/preview.png", RES "icons/preview-hover.png", 0, 0, NULL) {
	

	// LOAD IMAGE
	Image tmp_image = LoadImage(pz::globals::puzzle_image_path.c_str());
	if (tmp_image.height > IMAGE_MAX_HEIGHT) {
		const float scale = IMAGE_MAX_HEIGHT / static_cast<float>(tmp_image.height);
		int new_width = tmp_image.width * scale;
		int new_height = tmp_image.height * scale;
		while (new_width % PUZZLE_RECT_SIZE != 0) {
			new_width--;
		}
		while (new_height % PUZZLE_RECT_SIZE != 0) {
			new_height--;
		}
		ImageResize(&tmp_image, new_width, new_height);
	}
	this->image = LoadTextureFromImage(tmp_image);
	image_topleft.x = pz::SCREEN_W / 2.0f - this->image.width / 2.0f;
	image_topleft.y = (IMAGE_MAX_HEIGHT / 2.0f + TOP_BAR_HEIGHT + PADDING) - this->image.height / 2.0f;

	// INIT BUTTONS
	this->return_button.set_right(pz::SCREEN_W - PADDING);
	this->return_button.set_centery(TOP_BAR_HEIGHT / 2.0f);
	
	this->reset_button.set_right(this->return_button.get_left() - PADDING);
	this->reset_button.set_centery(TOP_BAR_HEIGHT / 2.0f);
		
	this->preview_button.set_right(this->reset_button.get_left() - PADDING);
	this->preview_button.set_centery(TOP_BAR_HEIGHT / 2.0f);

	// INIT PUZZLE
	this->reset_puzzle();
}


void pz::PuzzleScene::reset_puzzle() {
	grid_rows = static_cast<int>(this->image.height) / PUZZLE_RECT_SIZE;
	grid_cols = static_cast<int>(this->image.width) / PUZZLE_RECT_SIZE;
	this->puzzle_grid.clear();
	for (int i = 0; i < grid_rows; i++) {
		for (int j = 0; j < grid_cols; j++) {
			Rectangle puzzle_rect{ j * PUZZLE_RECT_SIZE, i * PUZZLE_RECT_SIZE, PUZZLE_RECT_SIZE, PUZZLE_RECT_SIZE };
			this->puzzle_grid.push_back({ true, puzzle_rect });
		}
	}
	this->puzzle_grid.back().first = false;	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(this->puzzle_grid.begin(), this->puzzle_grid.end() - 1, std::default_random_engine(seed));
}


void pz::PuzzleScene::update(const float dt) {
	this->return_button.update(dt);
	this->preview_button.update(dt);
	this->reset_button.update(dt);

	if (should_change_scene) {
		should_change_scene = false;
		pz::scene_manager_change_scene(pz::ChooseImageSceneID);
	}

	if (should_reset_puzzle) {
		should_reset_puzzle = false;
		this->reset_puzzle();
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

	}

}


void pz::PuzzleScene::draw() {
	DrawRectangleRec(TOP_BAR_RECT, TOP_BAR_COLOR);
	DrawLineEx(Vector2{ 0.0f, TOP_BAR_HEIGHT }, Vector2{ TOP_BAR_WIDTH, TOP_BAR_HEIGHT }, TOP_BAR_LINE_THICK, TOP_BAR_LINE_COLOR);
	
	this->return_button.draw();
	this->preview_button.draw();
	this->reset_button.draw();

	if (this->preview_button.is_hovered()) {
		DrawTextureV(this->image, image_topleft, WHITE);
		return;
	} 
	for (int i = 0; i < grid_rows; i++) {
		for (int j = 0; j < grid_cols; j++) {
			const std::pair<bool, Rectangle>& pair = this->puzzle_grid[i * grid_cols + j];
			if (pair.first == false) {
				continue;
			}			
			DrawTextureRec(
				this->image, 
				pair.second, 
				Vector2{
					image_topleft.x + j * PUZZLE_RECT_SIZE,
					image_topleft.y + i * PUZZLE_RECT_SIZE,
				}, 
				WHITE
			);
		}
	}		
	
}
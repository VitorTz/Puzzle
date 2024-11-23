#include "Scene.h"
#include <filesystem>
#include <iostream>


static pz::Grid grid{
	4,
	10.0f,
	100.0f,
	10.0f,
	10.0f	
};

static float y_pos = 0.0f;


pz::ChooseImageScene::ChooseImageScene() {
	grid.clear();
	const std::filesystem::path png_ext(".png");
	for (const auto& p : std::filesystem::directory_iterator(IMAGES_PATH)) {
		const std::filesystem::path& path = p.path();
		const std::filesystem::path p1 = path.extension();
		if (p.is_regular_file() && path.extension() == png_ext) {			
			grid.add_component(std::make_unique<pz::ImageComponent>(path.string().c_str()));			
		}
	}
	grid.move_vertical(y_pos);
}


void pz::ChooseImageScene::update(const float dt) {
	const float mouse_delta = GetMouseWheelMove();
	if (mouse_delta != 0.0f) {
		const float mov = mouse_delta * dt * pz::SCROLL_SPEED;
		y_pos += mov;
		grid.move_vertical(mov);
	}
	grid.update(dt);
	const pz::ImageComponent* image = dynamic_cast<pz::ImageComponent*>(grid.get_hovered_component());
	if (image != nullptr && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		pz::globals::puzzle_image_path = image->get_imagepath();
		pz::scene_manager_change_scene(pz::PuzzleSceneID);
	}
}


void pz::ChooseImageScene::draw() {
	grid.draw();
	DrawRectangleRec(
		Rectangle{ 0.0f, 0.0f, static_cast<float>(pz::SCREEN_W), 80.0f },
		Color{31, 32, 33, 255}
	);
	DrawLineEx(Vector2{ 0.0f, 80.0f }, Vector2{ pz::SCREEN_W, 80.0f }, 2.0f, WHITE);
	DrawText("Puzzle!", 10, 30, 40, WHITE);
	DrawText("Choose a image!", pz::SCREEN_W - 245, 40, 30, WHITE);
}
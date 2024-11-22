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


pz::ChooseImageScene::ChooseImageScene() {
	grid.clear();
	const std::filesystem::path png_ext(".png");
	for (const auto& p : std::filesystem::directory_iterator(IMAGES_PATH)) {
		const std::filesystem::path& path = p.path();
		const std::filesystem::path p1 = path.extension();
		if (p.is_regular_file() && path.extension() == png_ext) {			
			grid.add_component(std::make_unique<pz::Image>(path.string().c_str()));
		}
	}
}


void pz::ChooseImageScene::update(const float dt) {
	const float mouse_delta = GetMouseWheelMove();
	if (mouse_delta != 0.0f) {
		grid.move_vertical(mouse_delta * dt * 350.0f);
	}
	grid.update(dt);
}


void pz::ChooseImageScene::draw() {
	grid.draw();
}
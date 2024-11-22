#include "Scene.h"
#include <memory>


static std::unique_ptr<pz::Scene> scene{};
static pz::SceneID current_scene_id{};
static pz::SceneID next_scene_id{};
static bool should_change_scene{};


static void load_next_scene() {
	switch (next_scene_id) {
		case pz::ChooseImageSceneID:
			scene = std::make_unique<pz::ChooseImageScene>();
			break;
		case pz::PuzzleSceneID:
			scene = std::make_unique<pz::PuzzleScene>();
			break;
		default:
			break;
	}
	current_scene_id = next_scene_id;
	should_change_scene = false;
}


void pz::scene_manager_init() {
	load_next_scene();
}


void pz::scene_manager_change_scene(const pz::SceneID scene_id) {
	next_scene_id = scene_id;
	should_change_scene = true;
}


void pz::scene_manager_update(const float dt) {
	scene->update(dt);
	if (should_change_scene) {
		load_next_scene();
	}
}


void pz::scene_manager_draw() {
	scene->draw();
}
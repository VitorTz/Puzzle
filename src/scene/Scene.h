#pragma once
#include <vector>
#include "SceneID.h"
#include "../constants.h"
#include "../components/Component.h"
#include "../util/globals.h"


namespace pz {

	class Scene {
	public:
		~Scene() = default;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
	};

	class ChooseImageScene : public pz::Scene {
	public:
		ChooseImageScene();
		void update(float dt) override;
		void draw() override;
	};

	class PuzzleScene : public pz::Scene {

	private:
		Texture2D image{};
		pz::ImageButton return_button;
		pz::ImageButton reset_button;
		pz::ImageButton preview_button;
		std::vector<std::pair<bool, Rectangle>> puzzle_grid{};

	private:
		void reset_puzzle();

	public:
		PuzzleScene();
		void update(float dt) override;
		void draw() override;
	};


	void scene_manager_init();
	void scene_manager_update(float dt);
	void scene_manager_change_scene(pz::SceneID scene_id);
	void scene_manager_draw();

}
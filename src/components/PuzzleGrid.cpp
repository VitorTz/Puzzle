#include "Component.h"
#include <algorithm>
#include <raymath.h>
#include <random>
#include <chrono>
#include <iostream>


pz::PuzzleGrid::PuzzleGrid(
	const char* puzzle_image,
	const float puzzle_image_max_width,
	const float puzzle_image_max_height
) {
	// Load Image
	Image tmp_image = LoadImage(puzzle_image);
	// Resize
	float scale{ 1.0f };
	if (tmp_image.height > puzzle_image_max_height) {
		scale = puzzle_image_max_height / static_cast<float>(tmp_image.height);
	} 
	int new_width = tmp_image.width * scale;
	int new_height = tmp_image.height * scale;
	while (new_width % PUZZLE_RECT_SIZE != 0) {
		new_width--;
	}
	while (new_height % PUZZLE_RECT_SIZE != 0) {
		new_height--;
	}
	ImageResize(&tmp_image, new_width, new_height);
	// Load Texture
	this->image = LoadTextureFromImage(tmp_image);

	// Image Rect
	this->rows = static_cast<int>(this->image.height) / PUZZLE_RECT_SIZE;
	this->cols = static_cast<int>(this->image.width) / PUZZLE_RECT_SIZE;
	this->rect = {
		0.0f,
		0.0f,
		static_cast<float>(this->image.width),
		static_cast<float>(this->image.height)
	};
	
	this->reset();
	UnloadImage(tmp_image);
}


pz::PuzzleGrid::~PuzzleGrid() {
	UnloadTexture(this->image);
}


void pz::PuzzleGrid::reset() {
	const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	this->grid.clear();
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			this->grid.push_back(
				{
					false,
					Rectangle{
						static_cast<float>(j * pz::PUZZLE_RECT_SIZE),
						static_cast<float>(i * pz::PUZZLE_RECT_SIZE),
						static_cast<float>(pz::PUZZLE_RECT_SIZE),
						static_cast<float>(pz::PUZZLE_RECT_SIZE)
					}
				}
			);
		}
	}
	this->grid.back().first = true;
	std::shuffle(this->grid.begin(), this->grid.end() - 1, std::default_random_engine(seed));
}


void pz::PuzzleGrid::handle_input() {
	const Vector2 mouse_pos = GetMousePosition();

	if (this->should_move_rect == true) {
		return;
	}

	if (CheckCollisionPointRec(mouse_pos, this->rect) == false) {
		return;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == false) {
		return;
	}

	const Vector2 p = Vector2Subtract(mouse_pos, Vector2{ this->rect.x, this->rect.y });
	const int r = p.y / pz::PUZZLE_RECT_SIZE;
	const int c = p.x / pz::PUZZLE_RECT_SIZE;
	this->src_pos = Vector2{
		this->rect.x + c * pz::PUZZLE_RECT_SIZE,
		this->rect.y + r * pz::PUZZLE_RECT_SIZE
	};
	this->src_rect_index = r * this->cols + c;
	
	// Is a empty rect
	if (this->grid[this->src_rect_index].first == true) {
		return;
	}

	// Find empty rect
	const int deltas[4]{ -1, 1, this->cols, -this->cols };
	for (int i = 0; i < 4; i++) {
		this->dst_rect_index = this->src_rect_index + deltas[i];
		if (
			this->dst_rect_index >= 0 &&
			this->dst_rect_index < this->grid.size() &&
			this->grid[this->dst_rect_index].first == true
			) {
			this->should_move_rect = true;
			this->time = 0.0f;
			this->dst_pos = Vector2{
				this->rect.x + (this->dst_rect_index % this->cols) * pz::PUZZLE_RECT_SIZE,
				this->rect.y + (this->dst_rect_index / this->cols) * pz::PUZZLE_RECT_SIZE
			};
			return;
		}
	}
}


void pz::PuzzleGrid::move_rect(const float dt) {
	if (this->should_move_rect == false) {
		return;
	}

	this->time += dt;
	const float t = std::clamp(this->time / pz::TIME_TO_MOVE_A_PUZZLE_RECT, 0.0f, 1.0f);
	this->current_pos = Vector2Lerp(this->src_pos, this->dst_pos, t);

	if (t >= 1.0f) {
		this->should_move_rect = false;
		std::swap(this->grid.at(this->src_rect_index), this->grid.at(this->dst_rect_index));
	}
}


void pz::PuzzleGrid::update(const float dt) {
	this->handle_input();
	this->move_rect(dt);
}


void pz::PuzzleGrid::draw_preview() const {
	DrawTextureV(this->image, Vector2{this->rect.x, this->rect.y}, WHITE);
}


void pz::PuzzleGrid::draw() {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			const std::pair<bool, Rectangle>& p_rect = this->grid.at(i * this->cols + j);
			if (p_rect.first == true) { continue; }
			if (this->should_move_rect && i * this->cols + j == this->src_rect_index) {
				DrawTextureRec(this->image, p_rect.second, this->current_pos, WHITE);
			} else {
				DrawTextureRec(
					this->image,
					p_rect.second,
					Vector2{
						this->rect.x + j * pz::PUZZLE_RECT_SIZE,
						this->rect.y + i * pz::PUZZLE_RECT_SIZE
					},
					WHITE
				);
			}
		}
	}
}
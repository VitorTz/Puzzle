#include "Component.h"
#include "../constants.h"


pz::Grid::Grid(
	const int columns,
	const float pos_x,
	const float pos_y,
	const float padding_x,
	const float padding_y	
) : columns(columns),
	padding_x(padding_x), 
	padding_y(padding_y),
	max_width(static_cast<float>(pz::SCREEN_W / columns)),
	max_pos_x(static_cast<float>(pz::SCREEN_W) - padding_x),
	last_component_rect({pos_x, pos_y, -padding_x, 0.0f}) {
	this->rect.x = pos_x;
	this->rect.y = pos_y;	
}



pz::Component* pz::Grid::add_component(std::unique_ptr<pz::Component> c) {
	if (c->width() > this->max_width) {
		c->set_scale(this->max_width / c->width());
	}	

	const std::size_t num_childrens = this->children.size();
	const int col = num_childrens % this->columns;
	float x, y;

	if (num_childrens == 0) {
		x = this->rect.x;
		y = this->rect.y;		
	} else if (num_childrens >= this->columns) {
		x = col == 0 ? x = this->rect.x : this->children.back()->get_right() + this->padding_x;		
		y = this->children[num_childrens - this->columns]->get_bottom() + padding_y;		
	} else {
		x = this->children.back()->get_right() + padding_x;
		y = this->children.back()->get_top();
	}

	c->set_left(x);
	c->set_top(y);
	
	if (c->get_right() > this->max_pos_x) {
		const float scale = c->get_scale();
		c->set_scale(scale * (this->max_pos_x - c->get_left()) / c->width());
	}

	this->last_component_rect = c->get_rect();
	return pz::Component::add_component(std::move(c));	
}


void pz::Grid::move_horizontal(const float delta) {
	for (std::unique_ptr<pz::Component>& c : this->children) {
		c->set_left(c->get_left() + delta);
	}
}


void pz::Grid::move_vertical(const float delta) {
	for (std::unique_ptr<pz::Component>& c : this->children) {
		c->set_top(c->get_top() + delta);
	}
}


void pz::Grid::move(const float delta_horizontal, const float delta_vertical) {
	for (std::unique_ptr<pz::Component>& c : this->children) {
		c->set_left(c->get_left() + delta_horizontal);
		c->set_top(c->get_top() + delta_vertical);
	}
}


void pz::Grid::update(const float dt) {
	const Vector2 mouse_pos = GetMousePosition();
	this->hovered_component = nullptr;
	for (std::unique_ptr<pz::Component>& c : this->children) {
		if (CheckCollisionPointRec(mouse_pos, c->get_rect())) {
			this->hovered_component = c.get();
			this->border.set_rect(c->get_rect());
		}
	}
	pz::Component::update(dt);
}


void pz::Grid::draw() {
	pz::Component::draw();
	if (this->hovered_component != nullptr) {
		this->border.draw();
	}
}


void pz::Grid::clear() {
	this->children.clear();	
}


pz::Component* pz::Grid::get_hovered_component() {
	return this->hovered_component;
}
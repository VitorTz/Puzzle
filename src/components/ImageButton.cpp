#include "Component.h"


pz::ImageButton::ImageButton(
	const char* image_filepath,
	const char* hover_image,
	const float pos_x,
	const float pos_y,
	void (*action)()
) : action(action) {
	this->image = (pz::ImageComponent*) this->add_component(std::make_unique<pz::ImageComponent>(image_filepath));
	this->hover_image = (pz::ImageComponent*) this->add_component(std::make_unique<pz::ImageComponent>(hover_image));
	this->rect.x = pos_x;
	this->rect.y = pos_y;
	this->rect.width = this->image->width();
	this->rect.height = this->image->height();
}


void pz::ImageButton::update(const float dt) {
	if (
		this->action != NULL &&
		this->is_hovered() && 
		IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
	) {
		this->action();
	}
}

void pz::ImageButton::draw() {
	if (this->is_hovered()) {
		this->hover_image->set_left(this->rect.x);
		this->hover_image->set_top(this->rect.y);
		this->hover_image->draw();
	} else {
		this->image->set_left(this->rect.x);
		this->image->set_top(this->rect.y);
		this->image->draw();
	}
}
#include "Component.h"



Vector2 pz::Component::get_center() const {
	const Vector2 c{
		this->rect.x + this->rect.width / 2.0f,
		this->rect.y + this->rect.height / 2.0f
	};
	return c;
}


void pz::Component::set_center(const float x, const float y) {
	this->rect.x = x - this->rect.width * this->scale / 2.0f;
	this->rect.y = y - this->rect.height * this->scale / 2.0f;
}


float pz::Component::get_centerx() const {
	return this->rect.x + this->rect.width * this->scale / 2.0f;
}


void pz::Component::set_centerx(const float x) {
	this->rect.x = x - this->rect.width * this->scale / 2.0f;
}


float pz::Component::get_centery() const {
	return this->rect.y + this->rect.height * this->scale / 2.0f;
}


void pz::Component::set_centery(const float y) {
	this->rect.y = y - this->rect.height * this->scale / 2.0f;
}


float pz::Component::get_left() const {
	return this->rect.x;
}


void pz::Component::set_left(const float left) {
	this->rect.x = left;
}


float pz::Component::get_right() const {
	return this->rect.x + this->rect.width * this->scale;
}


void pz::Component::set_right(const float right) {
	this->rect.x = right - this->rect.width * this->scale;
}


float pz::Component::get_top() const {
	return this->rect.y;
}


void pz::Component::set_top(const float top) {
	this->rect.y = top;
}


float pz::Component::get_bottom() const {
	return this->rect.y + this->rect.height * this->scale;
}


void pz::Component::set_bottom(const float bottom) {
	this->rect.y = bottom - this->rect.height * this->scale;
}


Rectangle pz::Component::get_rect() const {
	const Rectangle rect{ 
		this->rect.x, 
		this->rect.y, 
		this->rect.width * this->scale, 
		this->rect.height * this->scale 
	};
	return rect;
}


pz::Component* pz::Component::add_component(std::unique_ptr<pz::Component> c) {
	this->children.emplace_back(std::move(c));
	return this->children.back().get();	
}


float pz::Component::width() const {
	return this->rect.width * this->scale;
}


float pz::Component::height() const {
	return this->rect.height * this->scale;
}


float pz::Component::get_scale() const {
	return this->scale;
}


void pz::Component::set_scale(const float scale) {
	this->scale = scale;
	for (std::unique_ptr<pz::Component>& c : this->children)
		c->set_scale(scale);
}


void pz::Component::update(const float dt) {
	for (std::unique_ptr<pz::Component>& c : this->children)
		c->update(dt);
}


void pz::Component::draw() {
	for (std::unique_ptr<pz::Component>& c : this->children)
		c->draw();
}


bool pz::Component::is_hovered() const {	
	return CheckCollisionPointRec(
		GetMousePosition(),
		this->get_rect()
	);
}

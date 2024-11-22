#include "Component.h"


pz::Border::Border() : pz::Border(1.0f, WHITE) { }

pz::Border::Border(
	const float thickness,
	const Color color
) : pz::Component("Border"),
	thickness(thickness),
	color(color) {

}


pz::Border::Border(
	const float thickness,
	const Color color,
	const Rectangle rect
) : pz::Border(thickness, color) {
	this->rect = rect;
}


float pz::Border::get_thickness() const {
	return this->thickness;
}


void pz::Border::set_thickness(const float thickness) {
	this->thickness = thickness;
}


Color pz::Border::get_color() const {
	return this->color;
}


void pz::Border::set_color(const Color& color) {
	this->color = color;
}


void pz::Border::set_rect(const Rectangle& rect) {
	this->rect = rect;
}


void pz::Border::draw() {
	pz::Component::draw();
	DrawRectangleLinesEx(this->rect, this->thickness, this->color);
}
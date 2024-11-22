#include "Component.h"


pz::Image::Image(
	const char* filepath
) : pz::Component(std::string(filepath)),
	texture(LoadTexture(filepath)) {
	this->rect = {
		0.0f,
		0.0f,
		static_cast<float>(this->texture.width),
		static_cast<float>(this->texture.height)
	};
}


pz::Image::~Image() {
	UnloadTexture(this->texture);
}


void pz::Image::draw() {	
	DrawTextureEx(this->texture, Vector2{this->rect.x, this->rect.y}, 0.0f, this->scale, WHITE);
	pz::Component::draw();
}
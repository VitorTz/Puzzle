#include "Component.h"
#include "../util/TexturePool.h"


pz::ImageComponent::ImageComponent(
	const char* filepath
) : imagepath(filepath),
	texture(pz::texture_pool_get(filepath)) {
	this->rect = {
		0.0f,
		0.0f,
		static_cast<float>(this->texture.width),
		static_cast<float>(this->texture.height)
	};
}


void pz::ImageComponent::draw() {	
	DrawTextureEx(this->texture, Vector2{this->rect.x, this->rect.y}, 0.0f, this->scale, WHITE);
	pz::Component::draw();
}


void pz::ImageComponent::change_image(const char* filepath) {
	if (this->texture.id > 0) {
		UnloadTexture(this->texture);
	}
	this->texture = LoadTexture(filepath);	
	this->rect.width = static_cast<float>(this->texture.width) * this->scale;
	this->rect.height = static_cast<float>(this->texture.height) * this->scale;
}


const std::string& pz::ImageComponent::get_imagepath() const {
	return this->imagepath;
}


const Texture2D& pz::ImageComponent::get_texture() const {
	return this->texture;
}
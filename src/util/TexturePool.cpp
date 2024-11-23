#include "TexturePool.h"
#include <unordered_map>
#include "util.h"


static std::unordered_map<std::size_t, Texture2D> pool{};


Texture2D pz::texture_pool_get(const char* filepath) {
	const std::size_t h = pz::hash_str(filepath);
	if (pool.find(h) == pool.end()) {
		pool.emplace(h, LoadTexture(filepath));
	}
	return pool[h];
}


void pz::texture_pool_clear() {
	for (auto& pair : pool) {
		UnloadTexture(pair.second);
	}
	pool.clear();
}
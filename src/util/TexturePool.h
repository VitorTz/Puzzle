#pragma once
#include <raylib.h>


namespace pz {


	Texture2D texture_pool_get(const char* filepath);
	void texture_pool_clear();

}
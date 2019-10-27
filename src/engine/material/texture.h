#pragma once
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "../../../dependencies.h"

namespace nerv
{
	class texture
	{
	private:
		//id of the texture
		size_t id;
		int width;
		int height;

		//nbChanels is if a texture is RGB, RGBA, ect...
		int nbChannels;

	public:

		texture();

		//create a texture for a file, for more info look into std_image.h
		//located in the dependencies folder.
		texture(std::string path);
		
		//getter
		inline int getWidth() { return this->width; }
		inline int getHeight() { return this->height; }
		inline int getnbChannels() { return this->nbChannels; }
		inline size_t getId() { return this->id; }

	};
}
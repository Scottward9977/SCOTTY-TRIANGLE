#pragma once
#define STB_IMAGE_IMPLEMENTATION

namespace SHADER_ {
	class Texture
	{
	public:
		void loadTextureImage(char* assetPath, bool flip, int filterMode, int wrapMode);
		void bind(unsigned int slot);

	private:

	};
}
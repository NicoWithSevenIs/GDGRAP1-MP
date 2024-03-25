#include "TexInfo.hpp"

/*.Cpp holds the texture information neeeded in program and prompts user of the texture status*/
TexInfo::TexInfo(std::string filename) {
	stbi_set_flip_vertically_on_load(true);
	this->tex_bytes = stbi_load(filename.c_str(), &this->img_width, &this->img_height, &this->colorChannels, 0);
	this->initialized = tex_bytes != NULL;

	std::cout << (initialized ? "Loaded Succesfully" : "Failed to Load Texture" ) << std::endl;

}

TexInfo::~TexInfo() {
	if (initialized) 
		stbi_image_free(this->tex_bytes);
}

unsigned char* TexInfo::getTexBytes() { return this->tex_bytes; }

bool TexInfo::isInitialized() { return this->initialized; }

GLuint* TexInfo::getTexture() { return &this->texture; }

int TexInfo::getWidth(){ return this->img_width;}
int TexInfo::getHeight(){ return this->img_height;}
int TexInfo::getColorChannels() { return this->colorChannels; }
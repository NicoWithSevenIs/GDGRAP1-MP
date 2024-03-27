#include "TexInfo.hpp"

/*.Cpp holds the texture information neeeded in program and prompts user of the texture status*/
TexInfo::TexInfo(std::string filename, std::string loadstring) {
	this->filename = filename;
	if (loadstring == "2D") {
		this->Load2dImage();
	}
	else if (loadstring == "CUBE") {
		this->LoadCubeImage();
	}
}

TexInfo::~TexInfo() {
	if (initialized) 
		stbi_image_free(this->tex_bytes);
}


void TexInfo::Load2dImage() {
	stbi_set_flip_vertically_on_load(true);
	this->tex_bytes = stbi_load(filename.c_str(), &this->img_width, &this->img_height, &this->colorChannels, 0);
	this->initialized = tex_bytes != NULL;

	std::cout << (initialized ? "Loaded Succesfully" : "Failed to Load Texture") << std::endl;
}

void TexInfo::LoadCubeImage() {

	std::vector<std::string> cubeFaces;
	cubeFaces.push_back("3d/Skybox/uw_rt.jpg");
	cubeFaces.push_back("3d/Skybox/uw_lf.jpg");
	cubeFaces.push_back("3d/Skybox/uw_up.jpg");
	cubeFaces.push_back("3d/Skybox/uw_dn.jpg");
	cubeFaces.push_back("3d/Skybox/uw_ft.jpg");
	cubeFaces.push_back("3d/Skybox/uw_bk.jpg");


	for (unsigned int i = 0; i < cubeFaces.size(); i++) {
		unsigned char* data = stbi_load(cubeFaces[i].c_str(), &img_width, &img_height, &colorChannels, 0);
		stbi_set_flip_vertically_on_load(false);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "texture failed to load" << std::endl;
			stbi_image_free(data);
		}
	}

	stbi_set_flip_vertically_on_load(false);

}

unsigned char* TexInfo::getTexBytes() { return this->tex_bytes; }

bool TexInfo::isInitialized() { return this->initialized; }

GLuint* TexInfo::getTexture() { return &this->texture; }

int TexInfo::getWidth(){ return this->img_width;}
int TexInfo::getHeight(){ return this->img_height;}
int TexInfo::getColorChannels() { return this->colorChannels; }
unsigned int* TexInfo::getSkyboxTexture() { return this->skyboxTexture; };
#include "TexInfo.hpp"
#include "../Utilities.h"

/*.Cpp holds the texture information neeeded in program and prompts user of the texture status*/
TexInfo::TexInfo(std::string filename) {

	stbi_set_flip_vertically_on_load(true);
	this->tex_bytes = stbi_load(filename.c_str(), &this->img_width, &this->img_height, &this->colorChannels, 0);
	this->initialized = tex_bytes != NULL;

	std::cout << (initialized ? "Loaded Succesfully" : "Failed to Load Texture" ) << std::endl;

}

TexInfo::TexInfo(int size) {
    std::string faceSkybox[]{
      "Skybox/underwater/uw_bk.jpg",
      "Skybox/underwater/uw_ft.jpg",

      "Skybox/underwater/uw_up.jpg",
      "Skybox/underwater/uw_dn.jpg",

      
      "Skybox/underwater/uw_lf.jpg",
      "Skybox/underwater/uw_rt.jpg"
      
    };
 
    for (unsigned int i = 0; i < size; i++) {
        int w, h, skyChannel;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data2 = stbi_load(faceSkybox[i].c_str(), &w, &h, &skyChannel, 0);
        this->datas.push_back(data2);
        this->vecWidth.push_back(w);
        this->vecHeight.push_back(h);
        this->vecColorChannels.push_back(skyChannel);
    }

    stbi_set_flip_vertically_on_load(true);

}

TexInfo::TexInfo(std::string filename1, std::string filename2) {


    stbi_set_flip_vertically_on_load(true);
    this->tex_bytes = stbi_load(filename1.c_str(), &this->img_width, &this->img_height, &this->colorChannels, 0);
    this->initialized = tex_bytes != NULL;

    stbi_set_flip_vertically_on_load(true);
    this->normal_bytes = stbi_load(filename2.c_str(), &img_width2, &img_height2, &colorChannels2, 0);
    this->initialized = normal_bytes != NULL;

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
std::vector<unsigned char*>* TexInfo::getSkyboxDatas() { return &this->datas; }
std::vector<int> TexInfo::getVecWidth() { return this->vecWidth; }
std::vector<int> TexInfo::getVecHeight() { return this->vecHeight; }
std::vector<int> TexInfo::getVecColorChannels() { return this->vecColorChannels; }
unsigned char* TexInfo::getNormalBytes() { return this->normal_bytes; }
int TexInfo::getWidth2() { return this->img_width2; }
int TexInfo::getHeight2() { return this->img_height2; }
int TexInfo::getColorChannels2() { return this->colorChannels2; }
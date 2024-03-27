#include "TexInfo.hpp"

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
 /*   std::string faceSkybox[]{
         "Skybox/underwater/uw_lf.jpg",
         "Skybox/underwater/uw_rt.jpg",
         "Skybox/underwater/uw_up.jpg",
         "Skybox/underwater/uw_dn.jpg",
         "Skybox/underwater/uw_ft.jpg",
         "Skybox/underwater/uw_bk.jpg"
    };*/
    
    
 /*   std::string faceSkybox[]{
         "Skybox/rainbow_rt.png",
         "Skybox/rainbow_lf.png",
         "Skybox/rainbow_up.png",
         "Skybox/rainbow_dn.png",
         "Skybox/rainbow_ft.png",
         "Skybox/rainbow_bk.png"
    };*/


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
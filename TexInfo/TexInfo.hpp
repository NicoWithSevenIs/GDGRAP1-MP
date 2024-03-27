#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "glad/glad.h"

#include <GLFW/glfw3.h> 
#include "../stb_image.h"


//Handles all texture loading
class TexInfo {
	
	private:
		std::string filename;
		bool initialized;

	private:
		int img_width;
		int img_height;
		int colorChannels;

	private:
		unsigned char* tex_bytes;
		GLuint texture;

		unsigned int* skyboxTexture;
		
	public:
		TexInfo(std::string filename, std::string loadstring);
		~TexInfo();
	
	public:
		void Load2dImage();
		void LoadCubeImage();

	public:
		unsigned char* getTexBytes();
		bool isInitialized();
		GLuint* getTexture();
		int getWidth();
		int getHeight();
		int getColorChannels();
		unsigned int* getSkyboxTexture();

};

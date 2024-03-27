#pragma once

#include <string>
#include <iostream>
#include "vector"

#include "glad/glad.h"

#include <GLFW/glfw3.h> 
#include "../stb_image.h"

//Handles all texture loading
class TexInfo {
	
	private:
		bool initialized;

	private:
		int img_width;
		int img_height;
		int colorChannels;

	private:
		std::vector<int> vecWidth;
		std::vector<int> vecHeight;
		std::vector<int> vecColorChannels;
	private:
		unsigned char* tex_bytes;
		std::vector<unsigned char*> datas;

		GLuint texture;
		
	public:
		TexInfo(std::string filename);

		TexInfo(int size);
		~TexInfo();

	public:
		unsigned char* getTexBytes();
		bool isInitialized();
		GLuint* getTexture();
		int getWidth();
		int getHeight();
		int getColorChannels();
		std::vector<unsigned char*>* getSkyboxDatas();
		std::vector<int> getVecWidth();
		std::vector<int> getVecHeight();
		std::vector<int> getVecColorChannels();

};

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
		bool initialized = false;

	private:
		int img_width;
		int img_height;
		int colorChannels;

		int img_width2;
		int img_height2;
		int colorChannels2;

	private:
		std::vector<int> vecWidth;
		std::vector<int> vecHeight;
		std::vector<int> vecColorChannels;
	private:
		unsigned char* tex_bytes;
		std::vector<unsigned char*> datas;
		unsigned char* normal_bytes;

		GLuint texture;
		
	public:
		TexInfo(std::string filename);
		TexInfo(int size);
		TexInfo(std::string filename1, std::string filename2);
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
		unsigned char* getNormalBytes();

};

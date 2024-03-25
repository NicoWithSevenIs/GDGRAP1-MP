#pragma once

#include <string>
#include <iostream>

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
		unsigned char* tex_bytes;
		GLuint texture;
		
	public:
		TexInfo(std::string filename);
		~TexInfo();

	public:
		unsigned char* getTexBytes();
		bool isInitialized();
		GLuint* getTexture();
		int getWidth();
		int getHeight();
		int getColorChannels();

};

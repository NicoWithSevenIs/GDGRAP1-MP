#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

//Handles all shader loading
class ShaderManager {
	private:
		GLuint* shaderProg;
	public:
		ShaderManager();
		~ShaderManager();
	public:
		void LoadShader(std::string path, unsigned int shader_type);
		GLuint* getShaderProg();
};


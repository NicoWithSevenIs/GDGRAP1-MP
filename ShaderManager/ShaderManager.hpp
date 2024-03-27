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
	private:
		GLuint* skyboxShader;
	public:
		ShaderManager();
		~ShaderManager();
	public:
		void LoadShader(std::string path, unsigned int shader_type);
		void LoadSkyboxShader(std::string path, unsigned int shader_type);
		GLuint* getShaderProg();
		GLuint* getSkyboxShader();
};


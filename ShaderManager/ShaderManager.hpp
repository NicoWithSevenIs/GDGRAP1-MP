#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
//Facade Singleton class that handles all shader loading
class ShaderManager {
	private:
		std::unordered_map<std::string, GLuint*> shaders;
		unsigned int skyboxShader;

	public:
		void LoadShader(std::string key, std::string path, unsigned int shader_type);
		
	/*
	
		Singleton
	
	*/

	private:
		static ShaderManager* instance;

	private:
		ShaderManager();
		~ShaderManager();
		ShaderManager(const ShaderManager&);
		ShaderManager& operator = (const ShaderManager&);
		static ShaderManager* getInstance();

	public:
		static void LoadShaders();
		static GLuint* getModelShader();
		static GLuint* getSkyboxShader();
};


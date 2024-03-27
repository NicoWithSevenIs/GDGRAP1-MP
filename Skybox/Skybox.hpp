#pragma once

#include "iostream"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ShaderManager/ShaderManager.hpp"
#include "../TexInfo/TexInfo.hpp"

class Skybox {
	private:
		unsigned int skyboxTexture;

	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

	public:
		Skybox(TexInfo* texture);

	public:
		void initializeBuffers();
		void Draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	
};
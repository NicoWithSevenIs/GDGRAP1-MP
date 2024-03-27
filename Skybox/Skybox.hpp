#pragma once


#include "../ShaderManager/ShaderManager.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../TexInfo/TexInfo.hpp"

#include "vector"
#include "string"
#include "iostream"

class Skybox {
	private:
		
	private:
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

	private:
		unsigned int texture;
		unsigned int skyboxVAO;
		unsigned int skyboxVBO;
		unsigned int skyboxEBO;

	public:
		Skybox(TexInfo texture);
	private:
		void initializeSkyboxTexture();
		void initializeSkyboxBuffers();
		void initializeSkyboxViewAndProjection();
	public:
		void Draw(ShaderManager& shader);

};
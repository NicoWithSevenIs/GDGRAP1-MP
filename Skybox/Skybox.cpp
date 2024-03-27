#include "Skybox.hpp"

Skybox::Skybox(TexInfo texture) {	
	
	this->initializeSkyboxBuffers();
	this->initializeSkyboxViewAndProjection();
}

void Skybox::initializeSkyboxTexture() {
	
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Skybox::initializeSkyboxBuffers() {
	
	float skyboxVertices[]{
	 -1.f, -1.f, 1.f,
	  1.f, -1.f, 1.f,
	  1.f, -1.f, -1.f,
	 -1.f, -1.f, -1.f,
	 -1.f, 1.f, 1.f,
	  1.f, 1.f, 1.f,
	  1.f, 1.f, -1.f,
	 -1.f, 1.f, -1.f
	};

	unsigned int skyboxIndices[]{
		1,2,6,
		6,5,1,

		0,4,7,
		7,3,0,

		4,5,6,
		6,7,4,

		0,3,2,
		2,1,0,

		0,1,5,
		5,4,0,

		3,7,6,
		6,2,3
	};

	glGenVertexArrays(1, &this->skyboxVAO);
	glGenBuffers(1, &this->skyboxVBO);
	glGenBuffers(1, &this->skyboxEBO);

	glBindVertexArray(this->skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
}

void Skybox::initializeSkyboxViewAndProjection() {
	this->projectionMatrix = glm::perspective(glm::radians(90.f), 1280.f/700.f, 0.1f, 100.f);
	glm::vec3 camera(0, 0, 0.f);

	glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f), camera * -1.0f);

	glm::vec3 WorldUp = glm::vec3(0, 1.0f, 0);
	glm::vec3 Center = glm::vec3(0, 0.f, 0);
	glm::vec3 Front = glm::vec3(Center - camera);
	Front = glm::normalize(Front);

	glm::vec3 Right = glm::normalize(glm::cross(Front, WorldUp));
	glm::vec3 Up = glm::normalize(glm::cross(Right, Front));

	//setup camera matrix //
	glm::mat4 cameraOrientation = glm::mat4(1.f);
	cameraOrientation[0][0] = Right.x;
	cameraOrientation[1][0] = Right.y;
	cameraOrientation[2][0] = Right.z;

	cameraOrientation[0][1] = Up.x;
	cameraOrientation[1][1] = Up.y;
	cameraOrientation[2][1] = Up.z;

	cameraOrientation[0][2] = -Front.x;
	cameraOrientation[1][2] = -Front.y;
	cameraOrientation[2][2] = -Front.z;

	this->viewMatrix = cameraOrientation * cameraPositionMatrix;
}

void Skybox::Draw(ShaderManager& shader) {
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glUseProgram(*shader.getSkyboxShader());

	glm::mat4 sky_view = glm::mat4(1.f);
	sky_view = glm::mat4(glm::mat3(viewMatrix));

	unsigned int skyboxViewLoc = glGetUniformLocation(*shader.getSkyboxShader(), "view");
	glUniformMatrix4fv(skyboxViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));

	unsigned int skyboxProjLoc = glGetUniformLocation(*shader.getSkyboxShader(), "projection");
	glUniformMatrix4fv(skyboxProjLoc, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}

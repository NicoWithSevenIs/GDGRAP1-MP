#include "Camera.hpp"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront):
	cameraPos(cameraPos),
	cameraFront(cameraFront),
	cameraUp(glm::vec3(0,1,0))
{}


glm::vec3 Camera::getCameraFront(){return this->cameraFront;}
glm::vec3 Camera::getCameraPos(){return this->cameraPos;}


void Camera::setCameraFront(glm::vec3 cameraFront) {
	this->cameraFront = cameraFront;
}

void Camera::setCameraPos(glm::vec3 cameraPos) {
	this->cameraPos = cameraPos;
}

void Camera::Draw(ShaderManager& shaders) {
	GLuint cameraPosAddress = glGetUniformLocation(*shaders.getShaderProg(), "cameraPos");
	glUniform3fv(cameraPosAddress, 1, glm::value_ptr(this->cameraPos));	
}
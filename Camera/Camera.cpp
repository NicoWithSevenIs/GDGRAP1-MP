#include "Camera.hpp"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront):
	cameraPos(cameraPos),
	cameraFront(cameraFront),
	cameraUp(glm::vec3(0,1,0))
{
	this->intiializedViewMatrix = glm::mat4(1.0f);
	this->initializedProjectionMatrix = glm::mat4(1.0f);
}


glm::vec3 Camera::getCameraFront(){return this->cameraFront;}
glm::vec3 Camera::getCameraPos(){return this->cameraPos;}


void Camera::setCameraFront(glm::vec3 cameraFront) {
	this->cameraFront = cameraFront;
}

void Camera::setCameraPos(glm::vec3 cameraPos) {
	this->cameraPos = cameraPos;
}

void Camera::Draw() {
	GLuint cameraPosAddress = glGetUniformLocation(*ShaderManager::getModelShader(), "cameraPos");
	glUniform3fv(cameraPosAddress, 1, glm::value_ptr(this->cameraPos));	
}

glm::mat4 Camera::getViewMatrix() {
	return this->intiializedViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
	return this->initializedProjectionMatrix;
}
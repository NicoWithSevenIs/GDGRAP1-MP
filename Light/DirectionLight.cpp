#include "DirectionLight.hpp"

DirectionLight::DirectionLight() {
	//this->lightColor = glm::vec3(0.75f, 0.75f, 0.75f);
	this->lightColor = glm::vec3(1.f, 1.f, 1.f);
	this->lightDirection = glm::vec3(0.f, 80.f, 0.f);
	this->ambientStr = 0.0000025f;
}

void DirectionLight::Draw() {
	
	auto modelShader = ShaderManager::getModelShader();

	GLuint directionLightBrightnessAddress = glGetUniformLocation(*modelShader, "directionLightBrightness");
	glUniform1f(directionLightBrightnessAddress, this->brightness);

	GLuint lightDirectionAddress = glGetUniformLocation(*modelShader, "directionLightDir");
	glUniform3fv(lightDirectionAddress, 1, glm::value_ptr(this->lightDirection));

	GLuint lightColorAddress = glGetUniformLocation(*modelShader, "directionLightColor");
	glUniform3fv(lightColorAddress, 1, glm::value_ptr(this->lightColor));

	GLuint ambientStrAddress = glGetUniformLocation(*modelShader, "directionLightAmbientStr");
	glUniform1f(ambientStrAddress, this->ambientStr);

	GLuint ambientColorAddress = glGetUniformLocation(*modelShader, "directionLightAmbientColor");
	glUniform3fv(ambientColorAddress, 1, glm::value_ptr(this->ambientColor));

	GLuint specStrAddress = glGetUniformLocation(*modelShader, "directionLightSpecStr");
	glUniform1f(specStrAddress, this->specStr);

	GLuint specPhongAddress = glGetUniformLocation(*modelShader, "directionLightSpecPhong");
	glUniform1f(specPhongAddress, this->specPhong);

}

void DirectionLight::setDirection(float x, float y, float z) {
	this->lightDirection = glm::vec3(x, y, z);
}

glm::vec3 DirectionLight::getLightDirection() {
	return this->lightDirection;
}


#include "DirectionLight.hpp"

DirectionLight::DirectionLight() {
	this->lightColor = glm::vec3(1.f, 1.f, 1.f);
	this->lightDirection = glm::vec3(0.f, -100.f, 0.f);
	this->ambientStr = 0.0025f;
}

void DirectionLight::Draw() {
	
	auto modelShader2 = ShaderManager::getModelShader2();

	GLuint directionLightBrightnessAddress2 = glGetUniformLocation(*modelShader2, "directionLightBrightness");
	glUniform1f(directionLightBrightnessAddress2, this->brightness);

	GLuint lightDirectionAddress2 = glGetUniformLocation(*modelShader2, "directionLightDir");
	glUniform3fv(lightDirectionAddress2, 1, glm::value_ptr(this->lightDirection));

	GLuint lightColorAddress2 = glGetUniformLocation(*modelShader2, "directionLightColor");
	glUniform3fv(lightColorAddress2, 1, glm::value_ptr(this->lightColor));

	GLuint ambientStrAddress2 = glGetUniformLocation(*modelShader2, "directionLightAmbientStr");
	glUniform1f(ambientStrAddress2, this->ambientStr);

	GLuint ambientColorAddress2 = glGetUniformLocation(*modelShader2, "directionLightAmbientColor");
	glUniform3fv(ambientColorAddress2, 1, glm::value_ptr(this->ambientColor));

	GLuint specStrAddress2 = glGetUniformLocation(*modelShader2, "directionLightSpecStr");
	glUniform1f(specStrAddress2, this->specStr);

	GLuint specPhongAddress2 = glGetUniformLocation(*modelShader2, "directionLightSpecPhong");
	glUniform1f(specPhongAddress2, this->specPhong);

}

void DirectionLight::DrawNormalMapped() {

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


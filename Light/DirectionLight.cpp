#include "DirectionLight.hpp"

DirectionLight::DirectionLight() {
	this->lightColor = glm::vec3(0.75f, 0.75f, 0.75f);
	this->lightDirection = glm::vec3(4.f, -5.f, 0.f);
}

void DirectionLight::Draw(ShaderManager& shaders) {


	GLuint directionLightBrightnessAddress = glGetUniformLocation(*shaders.getShaderProg(), "directionLightBrightness");
	glUniform1f(directionLightBrightnessAddress, this->brightness);

	GLuint lightDirectionAddress = glGetUniformLocation(*shaders.getShaderProg(), "directionLightDir");
	glUniform3fv(lightDirectionAddress, 1, glm::value_ptr(this->lightDirection));

	GLuint lightColorAddress = glGetUniformLocation(*shaders.getShaderProg(), "directionLightColor");
	glUniform3fv(lightColorAddress, 1, glm::value_ptr(this->lightColor));

	GLuint ambientStrAddress = glGetUniformLocation(*shaders.getShaderProg(), "directionLightAmbientStr");
	glUniform1f(ambientStrAddress, this->ambientStr);

	GLuint ambientColorAddress = glGetUniformLocation(*shaders.getShaderProg(), "directionLightAmbientColor");
	glUniform3fv(ambientColorAddress, 1, glm::value_ptr(this->ambientColor));

	GLuint specStrAddress = glGetUniformLocation(*shaders.getShaderProg(), "directionLightSpecStr");
	glUniform1f(specStrAddress, this->specStr);

	GLuint specPhongAddress = glGetUniformLocation(*shaders.getShaderProg(), "directionLightSpecPhong");
	glUniform1f(specPhongAddress, this->specPhong);

}

void DirectionLight::setDirection(float x, float y, float z) {
	this->lightDirection = glm::vec3(x, y, z);
}

glm::vec3 DirectionLight::getLightDirection() {
	return this->lightDirection;
}


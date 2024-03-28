#include "PointLight.hpp"

PointLight::PointLight() : Light() {
	this->lightPosition = glm::vec3(0.f, 50.f, 0.f);
	this->lightColor = glm::vec3(1.f, 1.f, 1.f);
	this->constant = 1.0f;
	this->linear = 0.027f;
	this->quadratic = 0.0028f;
}


void PointLight::Draw() {
	
	auto modelShader = ShaderManager::getModelShader();

	GLuint pointLightBrightnessAddress = glGetUniformLocation(*modelShader, "pointLightBrightness");
	glUniform1f(pointLightBrightnessAddress, this->brightness);

	GLuint lightAddress = glGetUniformLocation(*modelShader, "pointLightPos");
	glUniform3fv(lightAddress, 1, glm::value_ptr(this->lightPosition));

	GLuint lightColorAddress = glGetUniformLocation(*modelShader, "pointLightColor");
	glUniform3fv(lightColorAddress, 1, glm::value_ptr(this->lightColor));

	GLuint ambientStrAddress = glGetUniformLocation(*modelShader, "pointLightAmbientStr");
	glUniform1f(ambientStrAddress, this->ambientStr);

	GLuint ambientColorAddress = glGetUniformLocation(*modelShader, "pointLightAmbientColor");
	glUniform3fv(ambientColorAddress, 1, glm::value_ptr(this->ambientColor));

	GLuint baseConstantAddress = glGetUniformLocation(*modelShader, "constant");
	glUniform1f(baseConstantAddress, this->constant);

	GLuint baseLinearAddress = glGetUniformLocation(*modelShader, "linear");
	glUniform1f(baseLinearAddress, this->linear);

	GLuint baseQuadraticAddress = glGetUniformLocation(*modelShader, "quadratic");
	glUniform1f(baseQuadraticAddress, this->quadratic);

	GLuint specStrAddress = glGetUniformLocation(*modelShader, "pointLightSpecStr");
	glUniform1f(specStrAddress, this->specStr);

	GLuint specPhongAddress = glGetUniformLocation(*modelShader, "pointLightSpecPhong");
	glUniform1f(specPhongAddress, this->specPhong);

}



void PointLight::setConstant(float value) {
	this->constant = value;
}

void PointLight::setLinear(float value) {
	this->linear = value;
}

void PointLight::setQuadratic(float value) {
	this->quadratic = value;
}

float PointLight::getConstant() {
	return this->constant;
}

float PointLight::getLinear() {
	return this->linear;
}

float PointLight::getQuadratic() {
	return this->quadratic;
}
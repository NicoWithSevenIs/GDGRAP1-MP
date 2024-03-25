#include "Light.hpp"

Light::Light() {
	this->lightPosition = glm::vec3(0, 0, 0);
	this->lightColor = glm::vec3(1, 1, 1);
	this->ambientStr = 0.00025f;
	this->ambientColor = this->lightColor;
	this->specStr = 0.5f;
	this->specPhong = 16.f;
	this->brightness = 1.0f;
}

void Light::setPosition(glm::vec3 pos) {
	this->lightPosition = pos;
}

void Light::setColor(glm::vec3 color) {
	this->lightColor = color;
	this->ambientColor = this->lightColor;
}

glm::vec3 Light::getLightPosition() {
	return this->lightPosition;
}

glm::vec3 Light::getLightColor() {
	return this->lightColor;
}

void Light::setAmbientStr(float value) {
	this->ambientStr = value;
}
void Light::setSpecStr(float value) {
	this->specStr = value;
}

void Light::setSpecPhong(float value) {
	this->specPhong = value;
}

float Light::getAmbientStr() {
	return this->ambientStr;
}

glm::vec3 Light::getAmbientColor() {
	return this->ambientColor;
}

float Light::getSpecStr() {
	return this->specStr;
}

float Light::getSpecPhong() {
	return this->specPhong;
}

void Light::setBrightness(float value) {
	this->brightness = value;
}

float Light::getBrightness() {
	return this->brightness;
}
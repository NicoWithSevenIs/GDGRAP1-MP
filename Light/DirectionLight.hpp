#pragma once

#include "Light.hpp"


class DirectionLight : public Light {
	private:
		glm::vec3 lightDirection;
	public:
		DirectionLight();
	public:
		void Draw();
		void setDirection(float x, float y, float z);
		glm::vec3 getLightDirection();
};
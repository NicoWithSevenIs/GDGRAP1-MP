#pragma once

#include "Light.hpp"


class PointLight : public Light {
	private:
		float constant;
		float linear;
		float quadratic;
	public:
		PointLight();
	public:
		void Draw();
		void DrawNormalMapped();
	public:
		void setConstant(float value);
		void setLinear(float value);
		void setQuadratic(float value);
		float getConstant();
		float getLinear();
		float getQuadratic();
		void setPointLightFrontOfPlayer(glm::vec3 position);
};
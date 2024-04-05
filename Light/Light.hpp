#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ShaderManager/ShaderManager.hpp"

class Light {
	protected:
		glm::vec3 lightPosition;
		glm::vec3 lightColor;
	protected:
		float ambientStr;
		glm::vec3 ambientColor;

		float specStr;
		float specPhong;
	protected:
		float brightness;

	public:
		Light();

	public:
		virtual void Draw() = 0;
		virtual void DrawNormalMapped() = 0;
	public:
		void setPosition(glm::vec3 pos);
		void setColor(glm::vec3 color);
		glm::vec3 getLightPosition();
		glm::vec3 getLightColor();
		void setAmbientStr(float value);
		void setSpecStr(float value);
		void setSpecPhong(float value);
		float getAmbientStr();
		glm::vec3 getAmbientColor();
		float getSpecStr();
		float getSpecPhong();
		void setBrightness(float value);
		float getBrightness();
};
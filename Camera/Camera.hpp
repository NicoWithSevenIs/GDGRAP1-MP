#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ShaderManager/ShaderManager.hpp"

class Camera {
	
	protected:
		glm::mat4 viewMatrix;

		glm::vec3 cameraPos;
		glm::vec3 cameraUp;
		glm::vec3 cameraFront;

	protected:
		Camera(glm::vec3 cameraPos, glm::vec3 cameraFront);

	public:
		virtual void Draw(ShaderManager& shader);

	public:
		glm::vec3 getCameraPos();
		glm::vec3 getCameraFront();

	public:
		void setCameraPos(glm::vec3 cameraPos);
		void setCameraFront(glm::vec3 cameraFront);
		
	
};
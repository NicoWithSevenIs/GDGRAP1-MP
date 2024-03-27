#pragma once
#include "../Camera.hpp"
#include "../../Utilities.h"
#include "../../InputManager/InputManager.hpp"
#include "GLFW/glfw3.h"
class Perspective : public Camera {
	

	private:
		float fieldOfView;

	public:
		Perspective(glm::vec3 cameraPos, glm::vec3 cameraFront);

	public:
		void Draw();

};


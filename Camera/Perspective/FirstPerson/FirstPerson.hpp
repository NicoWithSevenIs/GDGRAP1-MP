#pragma once


#include "../PerspectiveCamera.hpp"

class FirstPerson : public Perspective {
	
	public:
		FirstPerson(glm::vec3 cameraPos, glm::vec3 cameraFront);

	public:
		void Draw();
		void DrawNormalMapped();
};
#pragma once


#include "../PerspectiveCamera.hpp"

class ThirdPerson :public Perspective {

	public:
		ThirdPerson(glm::vec3 cameraPos, glm::vec3 cameraFront);


	public:
		void Draw();


};
#pragma once


#include "../PerspectiveCamera.hpp"
#include "../../Transform/Transform.hpp"
class ThirdPerson :public Perspective {
	
	private:

		Transform* cameraSubject;
		float distanceFromSubject;
		float angleAroundSubject;
		float pitchTilt;
	 

	public:
		ThirdPerson(glm::vec3 cameraPos, glm::vec3 cameraFront, Transform* subject);


	public:
		void Draw();
		void DrawNormalMapped();


};
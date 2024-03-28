#pragma once

#include "../Model3D/Model3D.hpp"
#include "../Camera/Orthographic/OrthographicCamera.hpp"
#include "../Camera/Perspective/FirstPerson/FirstPerson.hpp"
#include "../Camera/Perspective/ThirdPerson/ThirdPerson.hpp"



class Player {


	private:
		Model3D playerModel;

		Camera* currentCamera;

		FirstPerson pCamera;
		ThirdPerson tCamera;
		Orthographic oCamera;

	public:
		Player(glm::vec3 position = glm::vec3(0,0,0));

	public:
		void addPlayerControls();
		void addCameraControls();

		void Draw();

		Camera* getCurrentCamera();
};
#pragma once


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <chrono>

#include "../ShaderManager/ShaderManager.hpp"
#include "../Model3D/Model3D.hpp"
#include "../InputManager/InputManager.hpp"

#include "../Camera/Camera.hpp"
#include "../Camera/Perspective/FirstPerson/FirstPerson.hpp"
#include "../Camera/Perspective/ThirdPerson/ThirdPerson.hpp"
#include "../Camera/Orthographic/OrthographicCamera.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../Light/PointLight.hpp"
#include "../Light/DirectionLight.hpp"

#include "../Skybox/Skybox.hpp"

class Workspace {
		
	private:
		
		GLFWwindow* window;

		std::vector<Model3D*> models;
		std::vector<Skybox*> skybox;

		PointLight pointLight;
		DirectionLight directionLight;

		bool isMovingLightSource;
	
		Camera* currentCamera;
		FirstPerson pCamera;
		ThirdPerson tCamera;
		Orthographic oCamera;


		
	private:
		bool awake();
		void start();
		void subscribe();
	private:
		void render();
		void update();
	private:
		void configureRotation(int index, glm::vec3 v, float thetaOffset);
	private:
		void setUnlit(bool value);
	public:
		void run();

	/* * * * * * * * * * *
	*	Singleton Stuff  *
	* * * * * * * * * * */

	private:
		static Workspace* instance;
	
	private:
		Workspace();
		Workspace(const Workspace&);
		Workspace& operator= (const Workspace&);

	public:
		static Workspace* getInstance();

};
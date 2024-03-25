#pragma once


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <chrono>

#include "../ShaderManager/ShaderManager.hpp"
#include "../Model3D/Model3D.hpp"
#include "../InputManager/InputManager.hpp"

#include "../Camera/Camera.hpp"
#include "../Camera/Perspective/PerspectiveCamera.hpp"
#include "../Camera/Orthographic/OrthographicCamera.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../Light/PointLight.hpp"
#include "../Light/DirectionLight.hpp"

class Workspace {
		
	private:
		
		GLFWwindow* window;
		ShaderManager shaders;

		std::vector<Model3D*> models;

		PointLight pointLight;
		DirectionLight directionLight;

		bool isMovingLightSource;
	
		Camera* currentCamera;
		Perspective pCamera;
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
		void processMainObjectXRotate(bool increase);
		void processMainObjectYRotate(bool increase);
		void processMainObjectZRotate(bool increase);
	private:
		void processLightSourceXRotate(bool increase);
		void processLightSourceYRotate(bool increase);
		void processLightSourceZRotate(bool increase);
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
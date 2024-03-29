#pragma once


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <chrono>

#include "../ShaderManager/ShaderManager.hpp"
#include "../Model3D/Model3D.hpp"
#include "../InputManager/InputManager.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../Light/PointLight.hpp"
#include "../Light/DirectionLight.hpp"

#include "../Skybox/Skybox.hpp"

#include "../Player/Player.hpp"

class Workspace {
		
	private:
		
		GLFWwindow* window;


		Player* player;
		std::vector<Model3D*> models;
		
		Skybox skybox;
		PointLight pointLight;
		DirectionLight directionLight;

		bool isMovingLightSource;
	
		


		
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
#include "Workspace.hpp"
#include "../Config.hpp"

Workspace::Workspace(): 
	pCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.f, 0.f, -1.0f)),
	oCamera(glm::vec3(0, 3.f, 0), glm::vec3(0.f, -1.f, -0.1f), OrthoData(3, -1, 100))
{
	this->window = NULL;

	this->isMovingLightSource = false;
	this->currentCamera = &pCamera;

	Utils::printVec3(currentCamera->getCameraFront());
}
Workspace::Workspace(const Workspace&) : Workspace() {}


//Initializes then returns whether the initialization was successful or not
bool Workspace::awake() {

	if (!glfwInit())
		return false;

	this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PC02-Tolentino_Nico/Ong_Lance", NULL, NULL);

	if (!window){
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(this->window);

	gladLoadGL();

	//Sets Input callbacks from Input Manager static methods
	glfwSetKeyCallback(this->window, InputManager::keyCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, InputManager::mouseCallback);


	glEnable(GL_DEPTH_TEST);

	return true;

}
 
/*Method calls in the needed shaders for the project*/
void Workspace::start() {

	ShaderManager::LoadShaders();

	/*
		"League Of Legends - Akali V3" (https://skfb.ly/ooKK6) 
		by 1FENIL is licensed under Creative Commons Attribution 
		(http://creativecommons.org/licenses/by/4.0/).

		Modified in blender to remove her weapons and scale her down (she was really big)
	*/
	skybox.push_back(new Skybox(new TexInfo(6)));
	models.push_back(new Model3D("3D/akali new.obj", new TexInfo("3D/akalitex.png") ));

	/*
		"Anemo Slime" (https://skfb.ly/oR8Kx)
		by LinjieFan is licensed under Creative Commons Attribution-NonCommercial 
		(http://creativecommons.org/licenses/by-nc/4.0/).
	*/

	models.push_back(new Model3D("3D/anemo.obj", new TexInfo("3D/anemo.png") ));
	models[1]->getTransform().setVector(TransformType::Translation, glm::vec3(5.f, 2.f, 0.f));
	models[1]->getTransform().setVector(TransformType::Scale, glm::vec3(0.15f, 0.15f, 0.15f));

	//see Transform
	models[1]->getTransform().overrideTransformationOrder(TransformType::RotationAxis, TransformType::Scale, TransformType::Translation);

}


//Subscribe subscribes delegates to the input manager's map of keyboard as key and vector of delegates as value
//+= operator is overloaded here, see input manager
void Workspace::subscribe() {

	std::unordered_map<int, PressData>& i = InputManager::getPressed();


	i[GLFW_KEY_SPACE] += [this]() {
		Utils::printVec3(currentCamera->getCameraFront());
	};

}


/*Draws in the models when cloning is enabled*/
void Workspace::render() {
	
	
	currentCamera->Draw();

	this->skybox[0]->Draw(currentCamera->getViewMatrix(), currentCamera->getProjectionMatrix());

	this->directionLight.Draw();
	this->pointLight.Draw();

	/*

	Extract the translation part of the transformed matrix
	(I forgor where i put my GDMATH notes so here's a youtube link instead HAHA)
	https://youtu.be/pdgK0YDjMEA?si=g5yYhY6wtxgl9ZiO&t=265

	*/

	this->pointLight.setPosition(models[1]->getTransform().getTransformedPosition());

	models[1]->Draw();
	this->setUnlit(true);

	models[0]->Draw();
	this->setUnlit(false);
	
}

//helper function for setting models unlit
void Workspace::setUnlit(bool value) {
	int toNum = static_cast<int>(value);
	if(toNum != 0)
		toNum /= toNum;

	GLuint isUnlitAddress = glGetUniformLocation(*ShaderManager::getModelShader(), "isUnlit");
	glUniform1i(isUnlitAddress, toNum);
}



void Workspace::update() {}


//Main Loop
void Workspace::run() {
	
	//Initialized Window, aborts execution when this fails
	if (!this->awake())
		return;

	//Initializes models and shaders
	this->start();

	//Assigns what to do for keyboard presses
	this->subscribe();
	
	while (!glfwWindowShouldClose(this->window))
	{	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//update for decor
		this->update();

		//draws everything
		this->render();

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	glfwTerminate();
	
}


/* * * * * * * * * * *
*	Singleton Stuff  *
* * * * * * * * * * */

Workspace* Workspace::instance = NULL;
Workspace* Workspace::getInstance() {
	if (!instance)
		instance = new Workspace();
	return instance;
}
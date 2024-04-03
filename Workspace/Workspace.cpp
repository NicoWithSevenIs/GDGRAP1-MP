#include "Workspace.hpp"
#include "../Config.hpp"

Workspace::Workspace() :
	skybox(TexInfo(6))
{	
	this->window = NULL;

	this->isMovingLightSource = false;


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

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	return true;

}
 
/*Method calls in the needed shaders for the project*/
void Workspace::start() {

	ShaderManager::LoadShaders();
	this->skybox.initialize();

	models.push_back(new Model3D("3D/submarine.obj", new TexInfo("3D/submarine.png"), false));
	models[0]->getTransform().setTranslation(glm::vec3(25.f, -15.f, 10.f));
	models[0]->getTransform().setScale(glm::vec3(0.15f, 0.15f, 0.15f));

	this->player = new Player();
	/*
		"League Of Legends - Akali V3" (https://skfb.ly/ooKK6) 
		by 1FENIL is licensed under Creative Commons Attribution 
		(http://creativecommons.org/licenses/by/4.0/).

		Modified in blender to remove her weapons and scale her down (she was really big)
	*/


	
	/*
		"Anemo Slime" (https://skfb.ly/oR8Kx)	
		by LinjieFan is licensed under Creative Commons Attribution-NonCommercial 
		(http://creativecommons.org/licenses/by-nc/4.0/).
	*/

	/*
	models.push_back(new Model3D("3D/anemo.obj", new TexInfo("3D/anemo.png") ));
	models[0]->getTransform().setVector(TransformType::Translation, glm::vec3(5.f, 2.f, 0.f));
	models[0]->getTransform().setVector(TransformType::Scale, glm::vec3(0.15f, 0.15f, 0.15f));

	//see Transform
	models[0]->getTransform().overrideTransformationOrder(TransformType::RotationAxis, TransformType::Scale, TransformType::Translation);
	*/
}


//Subscribe subscribes delegates to the input manager's map of keyboard as key and vector of delegates as value
//+= operator is overloaded here, see input manager
void Workspace::subscribe() {

	player->addCameraControls();
	player->addPlayerControls();
}


/*Draws in the models when cloning is enabled*/
void Workspace::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bool value;

	if (player->getCurrentCamera() != player->getFirstPersonCamera()) {
		GLint tintLoc = glGetUniformLocation(*ShaderManager::getSkyboxShader(), "tint");
		glUniform1i(tintLoc, 1);

		this->pointLight.setColor(glm::vec3(1.f, 1.f, 1.f));
		this->directionLight.setColor(glm::vec3(1.f, 1.f, 1.f));
		value = false;
		
	}
	else {
		this->pointLight.setColor(glm::vec3(0.f, 1.0f, 0.f));
		this->directionLight.setColor(glm::vec3(0.f, 1.0f, 0.f));
		value = true;
	}

	this->skybox.Draw(player->getCurrentCamera()->getViewMatrix(), player->getCurrentCamera()->getProjectionMatrix());
	this->setTint(value);

	auto modelShader2 = ShaderManager::getModelShader2();
	glUseProgram(*modelShader2);

	this->player->getCurrentCamera()->Draw();

	this->directionLight.Draw();
	this->pointLight.Draw();

	

	models[0]->Draw();

	auto modelShader = ShaderManager::getModelShader();
	glUseProgram(*modelShader);

	this->player->getCurrentCamera()->DrawNormalMapped();

	this->directionLight.DrawNormalMapped();
	this->pointLight.DrawNormalMapped();

	player->Draw();


	/*

	Extract the translation part of the transformed matrix
	(I forgor where i put my GDMATH notes so here's a youtube link instead HAHA)
	https://youtu.be/pdgK0YDjMEA?si=g5yYhY6wtxgl9ZiO&t=265

	*/

	//this->pointLight.setPosition(models[0]->getTransform().getTransformedPosition());

	//auto modelShader2 = ShaderManager::getModelShader2();
	//glUseProgram(*modelShader2);

	//this->directionLight.Draw();
	//this->pointLight.Draw();
	//
	//this->player->getCurrentCamera()->Draw();

	//models[0]->Draw();
	

	
}

//helper function for setting models unlit
void Workspace::setTint(bool value) {
	int toNum = static_cast<int>(value);
	if(toNum != 0)
		toNum /= toNum;

	GLuint isTintedAddress = glGetUniformLocation(*ShaderManager::getSkyboxShader(), "isTinted");
	glUniform1i(isTintedAddress, toNum);
}



void Workspace::update() {

	this->player->moveXZ(0.01f);
	this->player->moveY(0.01f);
	std::unordered_map<int, KeyData>& i = InputManager::getPressed();
	for (auto j : i) {
		j.second.Invoke();
	}


}


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
#include "Workspace.hpp"
#include "../Config.hpp"

Workspace::Workspace(): 
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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, InputManager::mouseCallback);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	return true;

}
 
/*Method calls in the needed shaders for the project*/
void Workspace::start() {

	ShaderManager::LoadShaders();
	this->player = new Player();
	this->skybox.initialize();

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
	
	

	this->skybox.Draw(player->getCurrentCamera()->getViewMatrix(), player->getCurrentCamera()->getProjectionMatrix());

	this->directionLight.Draw();
	this->pointLight.Draw();

	/*

	Extract the translation part of the transformed matrix
	(I forgor where i put my GDMATH notes so here's a youtube link instead HAHA)
	https://youtu.be/pdgK0YDjMEA?si=g5yYhY6wtxgl9ZiO&t=265

	*/

	//this->pointLight.setPosition(models[0]->getTransform().getTransformedPosition());
	//this->setUnlit(false);
	//models[0]->Draw();


	this->setUnlit(true);
	player->Draw();

	
}

//helper function for setting models unlit
void Workspace::setUnlit(bool value) {
	int toNum = static_cast<int>(value);
	if(toNum != 0)
		toNum /= toNum;

	GLuint isUnlitAddress = glGetUniformLocation(*ShaderManager::getModelShader(), "isUnlit");
	glUniform1i(isUnlitAddress, toNum);
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
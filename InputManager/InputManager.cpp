#include "InputManager.hpp"


void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	getInstance()->pressed[key].Invoke(action);
}


void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	
	InputManager* i = getInstance();
    

    if (i->firstMouseEnter)
    {
        i->previous = glm::vec2(xpos, ypos);
        i->firstMouseEnter = false;
        return;
    }

    i->delta = i->previous - glm::vec2(xpos,ypos);

}

//glm::vec3 InputManager::getCurrentLookAt(){return this->currentLookAt;}
glm::vec2 InputManager::getDelta(){return this->delta;}

/*Singleton Reference for organized coding purposes*/
InputManager* InputManager::instance = NULL;

InputManager::InputManager() {
    this->firstMouseEnter = true;
}

InputManager::InputManager(const InputManager&) {}

InputManager* InputManager::getInstance() {
	if (!instance) instance = new InputManager();
	return instance;
}

std::unordered_map<int, PressData>& InputManager::getPressed() {
	return getInstance()->pressed;
}




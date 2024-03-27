#include "InputManager.hpp"
#include "../Config.hpp"

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	getInstance()->pressed[key].action = action;
}


void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	
	InputManager* i = getInstance();
    
    //to prevent jumps between camera swithcing.
    //set isFirstMouseEnter to true when switching
    //handle first mouse enter in each respective update


    if (i->firstMouseEnter)
    {
        i->previousHover = glm::vec2(xpos, ypos);
        i->firstMouseEnter = false;
        return;
    }

    if(i->bSwitch)
        i->updateCurrentLookAt(xpos, ypos);
    else
        i->updateHoverDelta(xpos, ypos);
}


void InputManager::updateCurrentLookAt(float x, float y) {

    InputManager* i = getInstance();

    glm::vec2 offset = glm::vec2(x - i->previous.x, i->previous.y - y);
    i->previous = glm::vec2(x,y);

    offset *= i->sensitivity;
    
    i->rotation.x += offset.y;
    i->rotation.y += offset.x;

    i->rotation.x = std::clamp(i->rotation.x, -90.f, 90.f);
    i->rotation.y = std::clamp(i->rotation.y, -180.f, 0.f);

    glm::vec3 direction;


    direction.x = cos(glm::radians(i->rotation.y)) * cos(glm::radians(i->rotation.x));
    direction.y = sin(glm::radians(i->rotation.x));
    direction.z = sin(glm::radians(i->rotation.y)) * cos(glm::radians(i->rotation.x));

    
    i->currentLookAt = glm::normalize(direction);

}

glm::vec3 InputManager::getCurrentLookAt(){return this->currentLookAt;}



void InputManager::updateHoverDelta(float x, float y) {
    
    InputManager* i = getInstance();
    i->currentHover = glm::vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2) - glm::vec2(x, y);
    
}
glm::vec2 InputManager::getHoverDelta(){return this->currentHover;}






#pragma region Singleton

InputManager* InputManager::instance = NULL;

InputManager::InputManager() {
    this->firstMouseEnter = true;
    this->currentLookAt = glm::vec3(0,0,-1);
    this->rotation = glm::vec2(0.f, -90.f);
}

InputManager* InputManager::getInstance() {
	if (!instance) instance = new InputManager();
	return instance;
}

std::unordered_map<int, PressData>& InputManager::getPressed() {
	return getInstance()->pressed;
}
#pragma endregion



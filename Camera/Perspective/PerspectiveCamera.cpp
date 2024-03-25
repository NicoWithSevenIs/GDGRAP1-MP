#include "PerspectiveCamera.hpp"

Perspective::Perspective(glm::vec3 cameraPos, glm::vec3 cameraFront): Camera(cameraPos, cameraFront) {
    this->fieldOfView = 40.f;
}

void Perspective::Draw(ShaderManager& shader) {

    Camera::Draw(shader);
    //Utils::printVec3(cameraFront);

    //Retrieves the delta value of ScreenToViewport from InputManager then rotate the view matrix with it
  
    glm::vec2 delta = InputManager::getInstance()->getDelta();

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    //Slows down rotation speed
    delta *= 0.2;
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-delta.y), glm::vec3(1,0,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-delta.x), glm::vec3(0,1,0));

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->fieldOfView), 1280.f / 720.f, 0.1f, 100.f);
    
    unsigned int projectionLoc = glGetUniformLocation(*shader.getShaderProg(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(*shader.getShaderProg(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}


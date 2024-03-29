#pragma once

#include "ThirdPerson.hpp"

ThirdPerson::ThirdPerson(glm::vec3 cameraPos, glm::vec3 cameraFront, Transform* subject) :
    Perspective(cameraPos, cameraFront) {
    this->cameraSubject = subject;    
}



void ThirdPerson::Draw() {

    Camera::Draw();
    //Utils::printVec3(cameraFront);

    //Retrieves the delta value of ScreenToViewport from InputManager then rotate the view matrix with it

    glm::vec2 delta = InputManager::getInstance()->getHoverDelta();

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);  

    delta *= 0.2;
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-delta.y), glm::vec3(1,0,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-delta.x), glm::vec3(0,1,0));
    this->viewMatrix = viewMatrix;

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->fieldOfView), 1280.f / 720.f, 0.1f, 100.f);
    this->projectionMatrix = projectionMatrix;


    auto modelShader = ShaderManager::getModelShader();
    unsigned int projectionLoc = glGetUniformLocation(*modelShader, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(*modelShader, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}

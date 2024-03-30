#include "FirstPerson.hpp"


FirstPerson::FirstPerson(glm::vec3 cameraPos, glm::vec3 cameraFront):
Perspective(cameraPos, cameraFront){}

void FirstPerson::Draw() {
    
    Camera::Draw();

    this->cameraFront = InputManager::getInstance()->getCurrentLookAt();
    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    this->viewMatrix = viewMatrix;

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->fieldOfView), 1280.f / 720.f, 0.1f, 100.f);
    this->projectionMatrix = projectionMatrix;

    auto modelShader = ShaderManager::getModelShader();
    unsigned int projectionLoc = glGetUniformLocation(*modelShader, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(*modelShader, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

   /* auto modelShader2 = ShaderManager::getModelShader2();

    unsigned int projectionLoc2 = glGetUniformLocation(*modelShader2, "projection");
    glUniformMatrix4fv(projectionLoc2, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));

    unsigned int viewLoc2 = glGetUniformLocation(*modelShader2, "view");
    glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(viewMatrix));*/
}

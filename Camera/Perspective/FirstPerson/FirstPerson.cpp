#include "FirstPerson.hpp"


FirstPerson::FirstPerson(glm::vec3 cameraPos, glm::vec3 cameraFront):
Perspective(cameraPos, cameraFront){}

void FirstPerson::Draw() {
    
    Camera::Draw();

    this->cameraFront = InputManager::getInstance()->getCurrentLookAt();
    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->fieldOfView), 1280.f / 720.f, 0.1f, 100.f);

    auto modelShader = ShaderManager::getModelShader();
    unsigned int projectionLoc = glGetUniformLocation(*modelShader, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(*modelShader, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}

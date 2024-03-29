#pragma once

#include "ThirdPerson.hpp"
#include "../../Config.hpp"
#include <glm/gtc/matrix_transform.hpp>
ThirdPerson::ThirdPerson(glm::vec3 cameraPos, glm::vec3 cameraFront, Transform* subject) :
    Perspective(cameraPos, cameraFront) {
    
    
    this->cameraSubject = subject; 
    
    distanceFromSubject = 1.5f;
    angleAroundSubject = 90;
    pitchTilt = 20;
}



/*
Source: https://youtu.be/PoxDDZmctnU?si=3YK-AiXdd77h-8ON
*/
void ThirdPerson::Draw() {

    Camera::Draw();
    //Utils::printVec3(cameraFront);

    //Retrieves the delta value of ScreenToViewport from InputManager then rotate the view matrix with it

    glm::vec2 delta = InputManager::getInstance()->getHoverDelta();
    std::cout << delta.x << std::endl;

    float lookAngle = angleAroundSubject *  delta.x;

    ///std::cout << delta.x << std::endl;

    float horizontalDistance = distanceFromSubject * cos(glm::radians(pitchTilt));
    float verticalDistance = distanceFromSubject * sin(glm::radians(pitchTilt));

    float theta = cameraSubject->getYRotation() + lookAngle;
    float xOffset = horizontalDistance * cos(glm::radians(theta));
    float zOffset = horizontalDistance * sin(glm::radians(theta));

    glm::vec3 pos;

    pos.x = cameraSubject->getPosition().x - xOffset;
    pos.y = cameraSubject->getPosition().y + verticalDistance;
    pos.z = cameraSubject->getPosition().z - zOffset;

    std::cout << verticalDistance << std::endl;
    //Utils::printVec3(cameraSubject->getPosition());


   glm::mat4 viewMatrix = glm::lookAt(pos, cameraSubject->getPosition(), cameraUp);
  
  /*
   //pitch rotation
   viewMatrix = glm::rotate(viewMatrix, glm::radians(pitchTilt), glm::vec3(1, 0, 0));
   //yaw rotation
   viewMatrix = glm::rotate(viewMatrix, glm::radians(180 - theta), glm::vec3(0, 1, 0));
   viewMatrix = glm::translate(viewMatrix, pos);
   */
   this->viewMatrix = viewMatrix;

   /*
    glm::mat4 viewMatrix = glm::mat4(1.f);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(pitchTilt), glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(180 - theta), glm::vec3(0, 1, 0));
    glm::vec3 nPos = -pos;
    viewMatrix = glm::translate(viewMatrix, nPos);
    this->viewMatrix = viewMatrix;
       */
    //Utils::printVec3(viewMatrix[3]);
     
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->fieldOfView), 1280.f / 720.f, 0.1f, 100.f);
    this->projectionMatrix = projectionMatrix;


    auto modelShader = ShaderManager::getModelShader();
    unsigned int projectionLoc = glGetUniformLocation(*modelShader, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(*modelShader, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}


//delta *= 0.2;
  //;
  //viewMatrix = glm::rotate(viewMatrix, glm::radians(-delta.x), glm::vec3(0,1,0));
    
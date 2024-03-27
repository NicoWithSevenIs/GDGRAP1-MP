#include "PerspectiveCamera.hpp"
#include "../../Utilities.h"

Perspective::Perspective(glm::vec3 cameraPos, glm::vec3 cameraFront): Camera(cameraPos, cameraFront) {
    this->fieldOfView = 40.f;
}


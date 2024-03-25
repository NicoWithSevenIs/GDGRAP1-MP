#include "Transform.hpp"
#include <iostream>

/*.Cpp holds all the matrix transformation, along with storing/updating theta values*/
Transform::Transform() {
    this->Transforms[TransformType::Translation] = glm::vec3(0, 0, 0);
    this->Transforms[TransformType::Scale] = glm::vec3(1, 1, 1);
    this->Transforms[TransformType::RotationAxis] = glm::vec3(0, 1, 0);
    this->theta = 0;

    resetTransformationOrder();
}

float Transform::getTheta() { return this->theta; }
void Transform::setTheta(float theta) {
    this->theta = theta;
}

void Transform::setVector(TransformType type, glm::vec3 vec) {
    this->Transforms[type] = vec;
}

//Calculates Transform Matrix based on stored vector values

//Calls each delegate based on the order specified
//default is RSTI
//use overrideTransformationOrder to change this
glm::mat4 Transform::getTransformMatrix() {

    glm::mat4 transformMatrix = glm::mat4(1.0);

    std::unordered_map<TransformType, std::function<void(glm::mat4&)>> actions = {
        {TransformType::Translation, 
            [this](glm::mat4& transformMatrix) {  
                transformMatrix = glm::translate(transformMatrix, this->Transforms[TransformType::Translation]);  
            }
        },
        {TransformType::Scale,
            [this](glm::mat4& transformMatrix) {  
                transformMatrix = glm::scale(transformMatrix, this->Transforms[TransformType::Scale]);  
            }
        },
        {TransformType::RotationAxis, 
            [this](glm::mat4& transformMatrix) { 
                transformMatrix = glm::rotate(transformMatrix, glm::radians(this->theta), glm::normalize(this->Transforms[TransformType::RotationAxis]));
            }
        }
    };


    /*  
        Thinking of just making a vector of transformation instructions in the mp HAHA
        Calling it would go like this

        for(var t in transformSequence)
            actions[t](transformMatrix)
    */

    actions[this->first](transformMatrix);
    actions[this->second](transformMatrix);
    actions[this->third](transformMatrix);

    return transformMatrix;
}

glm::vec3 Transform::getVector(TransformType type) {
    return this->Transforms[type];
}

void Transform::incrementTheta(float amount) {
    this->theta += amount;
}


//make sure each transformation is unique
void Transform::overrideTransformationOrder(TransformType first, TransformType second, TransformType third) {
    if(first == second || second == third || first == third)
        return;

    this->first = first;
    this->second = second;
    this->third = third;
}

void Transform::resetTransformationOrder() {
    this->first = TransformType::Translation;
    this->second = TransformType::Scale;
    this->third = TransformType::RotationAxis;
}

glm::vec3 Transform::getTransformedPosition() {
    glm::mat4 transformedMatrix = this->getTransformMatrix();
    return transformedMatrix[3];
}
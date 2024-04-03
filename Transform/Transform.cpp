#include "Transform.hpp"

Transform::Transform() {
	translation = {0,0,0};
	scale = {1,1,1};
	rotation = glm::mat4(1.f);
}

void Transform::translate(glm::vec3 t) {
	translation += t;
}


glm::mat4 Transform::getTransformMatrix() {
	
	glm::mat4 transformMatrix = glm::mat4(1.f);

	transformMatrix = glm::translate(transformMatrix, translation);
	transformMatrix = glm::scale(transformMatrix, scale);
	transformMatrix = transformMatrix * rotation;

	return transformMatrix;
}

void Transform::setTranslation(glm::vec3 t) {
	this->translation = t;
}


void Transform::setRotation(glm::vec3 axis, float theta) {
	glm::mat4 rotation = glm::mat4(1.0);
	this->rotation = glm::rotate(rotation, theta, axis);
}

glm::vec3 Transform::getPosition() {
	glm::mat4 transformMatrix = this->getTransformMatrix();
	return transformMatrix[3];
}

glm::vec3 Transform::getTranslate() {
	return this->translation;
}

void Transform::setScale(glm::vec3 s) { this->scale = s; }
void Transform::Scale(glm::vec3 s) { this->scale += s; }

#include "../Utilities.h"

/*
Method 2
Reference: https://mmmovania.blogspot.com/2014/03/making-opengl-object-look-at-another.html?m=1
*/
void Transform::lookAt(glm::vec3 current, glm::vec3 target) {
	
	glm::vec3 delta = current - target;
	glm::vec3 up;
	glm::vec3 direction(glm::normalize(delta));

	if (abs(direction.x) < 0.00001 && abs(direction.z) < 0.00001) {
		if (direction.y > 0)
			up = glm::vec3(0.0, 0.0, -1.0); //if direction points in +y
		else
			up = glm::vec3(0.0, 0.0, 1.0); //if direction points in -y 
	}
	else {
		up = glm::vec3(0.0, 1.0, 0.0); //y-axis is the general up
	}
	up = glm::normalize(up);
	glm::vec3 right = glm::normalize(glm::cross(up, direction));
	up = glm::normalize(glm::cross(direction, right));

	this->rotation =  glm::mat4(right.x, right.y, right.z, 0.0f,
		up.x, up.y, up.z, 0.0f,
		direction.x, direction.y, direction.z, 0.0f,
		0, 0, 0, 1.0f);

}
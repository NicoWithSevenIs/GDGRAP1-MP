#pragma once

#include "Player.hpp"
#include <string>
Player::Player(glm::vec3 position):
	playerModel(Model3D("3D/akali new.obj", new TexInfo("3D/akalitex.png"))),
	pCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.f, 0.f, -1.0f)),
	tCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.f, 0.f, -1.0f), &playerModel.getTransform()),
	oCamera(glm::vec3(0, 5.f, 0), glm::vec3(0.f, -1.f, -0.1f), OrthoData(1.f, -1, 100))
{
	this->currentCamera = &pCamera;
	this->previousPos = position;

	this->xInput = 0.f;
	this->yInput = 0.f;
	this->zInput = 0.f;
}

void Player::addPlayerControls() {
	std::unordered_map<int, KeyData>& i = InputManager::getPressed();

	i[GLFW_KEY_W].onPress += [this]() {
		this->xInput = -1;
	};

	i[GLFW_KEY_W].onRelease += [this] {
		if (this->xInput < 0)
			this->xInput = 0.f;
	};


	i[GLFW_KEY_A].onPress += [this]() {
		this->zInput = -1;
	};

	i[GLFW_KEY_A].onRelease += [this] {
		if (this->zInput < 0)
			this->zInput = 0.f;
	};


	i[GLFW_KEY_S].onPress += [this]() {
		this->xInput = 1;
	};

	i[GLFW_KEY_S].onRelease += [this] {
		if (this->xInput > 0)
			this->xInput = 0.f;

	};


	i[GLFW_KEY_D].onPress += [this]() {
		this->zInput = 1;
	};

	i[GLFW_KEY_D].onRelease += [this] {
		if (this->zInput > 0)
			this->zInput = 0.f;
	};

	i[GLFW_KEY_E].onPress += [this]() {
		this->yInput = 1;
	};

	i[GLFW_KEY_E].onRelease += [this] {
		if (this->yInput > 0)
			this->yInput = 0.f;
	};


	i[GLFW_KEY_Q].onPress += [this]() {
		this->yInput = -1;
	};

	i[GLFW_KEY_Q].onRelease += [this] {
		if (this->yInput < 0)
			this->yInput = 0.f;
	};
}

void Player::addCameraControls() {
	std::unordered_map<int, KeyData>& i = InputManager::getPressed();

	float cameraSpeed = 0.01f;


	i[GLFW_KEY_1].onPress += [this]() {
		this->currentCamera = &this->pCamera;
		InputManager::getInstance()->setSwitch(true);
	};

	i[GLFW_KEY_2].onPress += [this]() {
		this->currentCamera = &this->oCamera;
	};

	i[GLFW_KEY_3].onPress += [this]() {
		this->currentCamera = &this->tCamera;
		InputManager::getInstance()->setSwitch(false);
	};

	
	
	i[GLFW_KEY_UP].onPress += [this, cameraSpeed]() {
	pCamera.setCameraPos(pCamera.getCameraPos() + cameraSpeed * pCamera.getCameraFront());
	};

	i[GLFW_KEY_LEFT].onPress += [this, cameraSpeed]() {
		pCamera.setCameraPos(pCamera.getCameraPos() - cameraSpeed * (
			glm::normalize(glm::cross(pCamera.getCameraFront(), glm::vec3(0, 1, 0)))));
	};

	i[GLFW_KEY_DOWN].onPress += [this, cameraSpeed]() {
		pCamera.setCameraPos(pCamera.getCameraPos() - cameraSpeed * pCamera.getCameraFront());
	};

	i[GLFW_KEY_RIGHT].onPress += [this, cameraSpeed]() {
		pCamera.setCameraPos(pCamera.getCameraPos() + cameraSpeed * (
			glm::normalize(glm::cross(pCamera.getCameraFront(), glm::vec3(0, 1, 0)))));
	};





}

float theta = 0.f;
void Player::moveXZ(float speed) {
	
	getPlayerTransform().lookAt(pCamera.getCameraPos(), pCamera.getCameraPos() - pCamera.getCameraFront());
	/*
	glm::vec3 direction = glm::vec3(zInput, 0, xInput);

	if(direction == glm::vec3(0,0,0))
		return;
	
	direction = glm::normalize(direction) * speed;

	glm::vec3 previous = getPlayerTransform().getPosition();
	getPlayerTransform().translate(direction);

	Utils::printVec3(getPlayerTransform().getPosition());
	glm::vec3 current = getPlayerTransform().getPosition();
	*/

	
	/*my alg
		glm::vec3 lookDir = glm::normalize(current-previous);
		float angle = atan2(lookDir.x, lookDir.z) * 180 / 3.14;
		getPlayerTransform().setRotation({0,1,0}, angle);
	*/

	//alg i grabbed off the net


}

void Player::moveY(float speed) {
	if(yInput == 0)
		return;

	glm::vec3 movementVector = glm::vec3(0, yInput, 0) * speed;
	getPlayerTransform().translate(movementVector);
}

void Player::Draw() {
	currentCamera->Draw();

	//float delta = InputManager::getInstance()->getHoverDelta().x / SCREEN_WIDTH - 0.5f;
	//getPlayerTransform().setTheta(delta*180);
	playerModel.Draw();
}

Camera* Player::getCurrentCamera() {
	return this->currentCamera;
}


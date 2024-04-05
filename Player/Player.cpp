#pragma once

#include "Player.hpp"
#include <string>
Player::Player(glm::vec3 position):
	playerModel("3D/SubLow0Smooth.obj", new TexInfo("3D/fish.png", "3D/fish_normal.png"), true),
	pCamera(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(0.f, 0.f, -1.0f)),
	tCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.f, 0.f, -1.0f), &playerModel.getTransform()),
	oCamera(glm::vec3(0, 5.f, 0), glm::vec3(0.f, -1.f, -0.1f), OrthoData(1.f, -1, 100))
{	

	this->playerModel.getTransform().setScale(glm::vec3(0.001027f, 0.001027f, 0.001027f));

	this->currentCamera = &pCamera;
	this->previousPos = position;

	getPlayerTransform().translate({0, -5, 0});

	getPlayerTransform().setScale(glm::vec3(0.001027f, 0.001027f, 0.001027f));
	

	this->xInput = 0.f;
	this->yInput = 0.f;
	this->zInput = 0.f;
}

void Player::addPlayerControls() {
	std::unordered_map<int, KeyData>& i = InputManager::getPressed();

	i[GLFW_KEY_W].onPress += [this]() {
		this->zInput = -1;
	};

	i[GLFW_KEY_W].onRelease += [this] {
		if (this->zInput < 0)
			this->zInput = 0.f;
	};


	i[GLFW_KEY_A].onPress += [this]() {
		this->xInput = -1;
	};

	i[GLFW_KEY_A].onRelease += [this] {
		if (this->xInput < 0)
			this->xInput = 0.f;
	};


	i[GLFW_KEY_S].onPress += [this]() {
		this->zInput = 1;
	};

	i[GLFW_KEY_S].onRelease += [this] {
		if (this->zInput > 0)
			this->zInput = 0.f;

	};


	i[GLFW_KEY_D].onPress += [this]() {
		this->xInput = 1;
	};

	i[GLFW_KEY_D].onRelease += [this] {
		if (this->xInput > 0)
			this->xInput = 0.f;
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
		oCamera.setCameraPos(getPlayerTransform().getPosition());
		
	};

	i[GLFW_KEY_3].onPress += [this]() {
		this->currentCamera = &this->tCamera;
		InputManager::getInstance()->setSwitch(false);
	};

	
	
	i[GLFW_KEY_UP].onPress += [this, cameraSpeed]() {
		if (currentCamera != &oCamera)
			return;
		auto cPos = oCamera.getCameraPos();
		oCamera.setCameraPos({cPos.x, cPos.y, cPos.z+cameraSpeed});
	};

	i[GLFW_KEY_LEFT].onPress += [this, cameraSpeed]() {
	
		if (currentCamera != &oCamera)
			return;
		auto cPos = oCamera.getCameraPos();
		oCamera.setCameraPos({ cPos.x + cameraSpeed, cPos.y, cPos.z });
		
	};

	i[GLFW_KEY_DOWN].onPress += [this, cameraSpeed]() {
		if (currentCamera != &oCamera)
			return;
		auto cPos = oCamera.getCameraPos();
		oCamera.setCameraPos({ cPos.x, cPos.y, cPos.z - cameraSpeed });
	};

	i[GLFW_KEY_RIGHT].onPress += [this, cameraSpeed]() {
		
		if (currentCamera != &oCamera)
			return;
		auto cPos = oCamera.getCameraPos();
		oCamera.setCameraPos({ cPos.x - cameraSpeed, cPos.y, cPos.z});
	
	};

}

void Player::moveXZ(float speed, PointLight* pointLight) {
	glm::vec3 direction = glm::vec3(xInput, 0, zInput);
	


	if (currentCamera == &oCamera)
		return;

	

	if (currentCamera == &pCamera) {
		
		glm::vec3 cPos = pCamera.getCameraPos();
		pCamera.setCameraPos(
			glm::vec3(cPos.x + xInput * speed, cPos.y, cPos.z + zInput * speed)
		);
	
		getPlayerTransform().setTranslation(pCamera.getCameraPos());
		getPlayerTransform().lookAt(pCamera.getCameraPos(), pCamera.getCameraPos() - pCamera.getCameraFront());
		pointLight->setPosition(pCamera.getCameraFront() + pCamera.getCameraPos());
	
	}
	else if (currentCamera == &tCamera) {

		if (direction == glm::vec3(0, 0, 0))
			return;

		direction = glm::normalize(direction) * speed;
		glm::vec3 previous = getPlayerTransform().getPosition();
		getPlayerTransform().translate(direction);
		glm::vec3 current = getPlayerTransform().getPosition();
		getPlayerTransform().lookAt(current, previous);
		pointLight->setPosition(pCamera.getCameraFront() + pCamera.getCameraPos());
	}


	/*my old alg

		glm::vec3 current = pCamera.getCameraPos();
		glm::vec3 target = pCamera.getCameraPos() - pCamera.getCameraFront();
		glm::vec3 lookDir = glm::normalize(current - target);
		float angle = atan2(lookDir.x, lookDir.z) * 180 / 3.14;
		getPlayerTransform().setRotation({ 0,1,0 }, angle);
	*/
	

}

void Player::moveY(float speed, PointLight* pointLight) {

	if(currentCamera == &oCamera)
		return;

	Utils::printVec3(getPlayerTransform().getPosition());
	if (yInput == 0 || getPlayerTransform().getPosition().y + yInput * speed >= 1)
		return;

	if (currentCamera == &pCamera) {
		glm::vec3 cPos = pCamera.getCameraPos();
		pCamera.setCameraPos({ cPos.x, cPos.y + yInput * speed, cPos.z});
		pointLight->setPosition(pCamera.getCameraFront() + pCamera.getCameraPos());
	}
	else {
		glm::vec3 movementVector = glm::vec3(0, yInput * speed, 0);
		getPlayerTransform().translate(movementVector);
		pointLight->setPosition(pCamera.getCameraFront() + pCamera.getCameraPos());
	}
	
}

void Player::Draw() {
	//currentCamera->Draw();

	//float delta = InputManager::getInstance()->getHoverDelta().x / SCREEN_WIDTH - 0.5f;
	//getPlayerTransform().setTheta(delta*180);
	playerModel.DrawNormalMapped();
}

Camera* Player::getCurrentCamera() {
	return this->currentCamera;
}

FirstPerson* Player::getFirstPersonCamera() {
	return &this->pCamera;
}
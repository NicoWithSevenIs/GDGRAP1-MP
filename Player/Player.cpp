#pragma once

#include "Player.hpp"

Player::Player(glm::vec3 position):
	playerModel(Model3D("3D/akali new.obj", new TexInfo("3D/akalitex.png"))),
	pCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.f, 0.f, -1.0f)),
	tCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.f, 0.f, -1.0f)),
	oCamera(glm::vec3(0, 5.f, 0), glm::vec3(0.f, -1.f, -0.1f), OrthoData(1.f, -1, 100))
{
	this->currentCamera = &pCamera;
}

void Player::addPlayerControls() {



}

void Player::addCameraControls() {
	std::unordered_map<int, PressData>& i = InputManager::getPressed();

	float cameraSpeed = 0.01f;


	i[GLFW_KEY_1] += [this]() {
		this->currentCamera = &this->pCamera;
		InputManager::getInstance()->setSwitch(true);
	};

	i[GLFW_KEY_2] += [this]() {
		this->currentCamera = &this->oCamera;
	};

	i[GLFW_KEY_3] += [this]() {
		this->currentCamera = &this->tCamera;
		InputManager::getInstance()->setSwitch(false);
	};




	i[GLFW_KEY_W] += [this, cameraSpeed]() {
		pCamera.setCameraPos(pCamera.getCameraPos() + cameraSpeed * pCamera.getCameraFront());
	};

	i[GLFW_KEY_A] += [this, cameraSpeed]() {
		pCamera.setCameraPos(pCamera.getCameraPos() - cameraSpeed * (
			glm::normalize(glm::cross(pCamera.getCameraFront(), glm::vec3(0, 1, 0)))));
	};

	i[GLFW_KEY_S] += [this, cameraSpeed]() {
		pCamera.setCameraPos(pCamera.getCameraPos() - cameraSpeed * pCamera.getCameraFront());
	};

	i[GLFW_KEY_D] += [this, cameraSpeed]() {
		pCamera.setCameraPos(pCamera.getCameraPos() + cameraSpeed * (
			glm::normalize(glm::cross(pCamera.getCameraFront(), glm::vec3(0, 1, 0)))));
	};


}

void Player::Draw() {
	currentCamera->Draw();
	playerModel.Draw();
}

Camera* Player::getCurrentCamera() {
	return this->currentCamera;
}
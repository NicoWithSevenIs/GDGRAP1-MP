#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <functional>
#include <vector>

#include "../../Utilities.h"

struct PressData {
	 
	int action = 0;
	std::vector<std::function<void()>> onPress;


	void Invoke(int action) {
		if(action == GLFW_RELEASE)
			return;

		for (auto f : onPress)
			f(); 
	}

	PressData& operator += (const std::function<void()>& f) {
		onPress.push_back(f);
		return *this;
	}

	void Clear() {
		onPress.clear();
	}

};

class InputManager {

	//Keyboard
	private:
		std::unordered_map<int, PressData> pressed;

	//Mouse
	private:
		bool firstMouseEnter = true;

		//stores viewport coordinate data
		glm::vec2 previous;
		glm::vec2 delta;

	private:
		static InputManager* instance;

	private:
		InputManager();
		InputManager(const InputManager&);
		InputManager& operator=(const InputManager&);


	public:
		glm::vec2 getDelta();

	public:
		static InputManager* getInstance();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

		static std::unordered_map<int, PressData>& getPressed();

		
};
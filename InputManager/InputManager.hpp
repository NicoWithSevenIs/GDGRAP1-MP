#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include <functional>
#include <algorithm>

#include <vector>
#include <unordered_map>


#include "../../Utilities.h"

struct Action {

	private:
		std::vector<std::function<void()>> actionList;


	public:
		void Invoke() {
			for (auto f : actionList)
				f();
		}

		Action& operator += (const std::function<void()>& f) {
			actionList.push_back(f);
			return *this;
		}

		void Clear() {
			actionList.clear();
		}
};

struct KeyData {
	 
	int action = 0;
	
	Action onPress;
	Action onRelease;

	void Invoke() {
		switch (action) {
			case GLFW_PRESS:
			case GLFW_REPEAT:
				onPress.Invoke();
			break;
			case GLFW_RELEASE: 
				onRelease.Invoke();
		}
	}

};

class InputManager {

	//Keyboard
	private:
		std::unordered_map<int, KeyData> pressed;

	/*Mouse*/


	private:
		bool bSwitch = true;
		bool firstMouseEnter = true;

	//Third-Person Camera
	private:
		//stores viewport coordinate data
		glm::vec2 previousHover;
		glm::vec2 currentHover;

	public:
		void updateHoverDelta(float x, float y);
		glm::vec2 getHoverDelta();


	//First-Person Camera
	private:
		float sensitivity = 0.1f;
		glm::vec2 previous;
		glm::vec2 rotation;
		

		glm::vec3 currentLookAt;
	public:
		void updateCurrentLookAt(float x, float y);
		glm::vec3 getCurrentLookAt();

		void setSwitch(bool val) {
			this->bSwitch = val;
			this->firstMouseEnter = true;
		}
		




	#pragma region Singleton
	private:
		static InputManager* instance;

	private:
		InputManager();
		InputManager(const InputManager&);
		InputManager& operator=(const InputManager&);

	public:
		static InputManager* getInstance();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

		static std::unordered_map<int, KeyData>& getPressed();
	#pragma endregion
		
};
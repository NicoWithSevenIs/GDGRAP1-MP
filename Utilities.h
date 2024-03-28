
#pragma once
#include "glm/glm.hpp"
#include <iostream>
class Utils {

	public:




		static void printVec3(glm::vec3 vec) {
			std::cout << "{ "  << vec.x << "," << vec.y << "," <<  vec.z  <<   "}" <<std::endl;
		
		}

		static void printVec2(glm::vec2 vec) {
			std::cout << "{ " << vec.x << "," << vec.y << "}" << std::endl;

		}

		static void Log(std::string msg) {
			std::cout << msg << std::endl;
		}
};

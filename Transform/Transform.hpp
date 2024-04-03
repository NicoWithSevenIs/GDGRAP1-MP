#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


#include <unordered_map>
#include <functional>
#include <cmath>


/*Holds all transform data for Model3D*/
class Transform {

	private:
		//glm::mat4 transformMatrix;
		glm::vec3 translation;
		glm::vec3 scale;
		glm::mat4 rotation;
	

	public:
		Transform();

	public:
		void translate(glm::vec3 t);
		//void moveTo(glm::vec3 dest);
		void setTranslation(glm::vec3 t);
		void setRotation(glm::vec3 axis, float theta);

		void lookAt(glm::vec3 current, glm::vec3 target);

		glm::mat4 getTransformMatrix();
		glm::vec3 getPosition();
		glm::vec3 getTranslate();
		void setScale(glm::vec3 s);
		void Scale(glm::vec3 s);
		
};
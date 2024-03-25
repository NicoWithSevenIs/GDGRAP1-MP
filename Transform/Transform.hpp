#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>
#include <functional>

enum class TransformType: int {
	Translation,
	Scale,
	RotationAxis,
};


/*Holds all transform data for Model3D*/
class Transform {

	private:
		std::unordered_map<TransformType, glm::vec3> Transforms;
		float theta;

		TransformType first;
		TransformType second;
		TransformType third;

	public:
		Transform();

	public:
		void setTheta(float theta);
		void incrementTheta(float amount);
		float getTheta();

		void setVector(TransformType type, glm::vec3 vec);
		glm::vec3 getVector(TransformType type);

		void overrideTransformationOrder(TransformType first, TransformType second, TransformType third);
		void resetTransformationOrder();

		glm::mat4 getTransformMatrix();
		glm::vec3 getTransformedPosition();

};
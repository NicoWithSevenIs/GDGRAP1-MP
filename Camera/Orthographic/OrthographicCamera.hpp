#pragma once

#include "../Camera.hpp"

struct OrthoData {

	float left;
	float right;
	float bottom;
	float top;
	float znear;
	float zfar;

	OrthoData(float size, float znear,float zfar):
		left(-size), right(size), bottom(-size), top(size), znear(znear), zfar(zfar)
	{}

};

class Orthographic : public Camera {
	

	private:
		OrthoData orthoData;

	public:
		Orthographic(glm::vec3 cameraPos, glm::vec3 cameraFront, OrthoData orthoData);

	public:
		void Draw();
	

};
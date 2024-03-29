#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "../Transform/Transform.hpp"
#include "../ObjData/ObjData.hpp"
#include "../ShaderManager/ShaderManager.hpp"
#include "../TexInfo/TexInfo.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

class Model3D {

	private:
		Transform transform;
		ObjData modelInfo;

		GLuint VAO;
		GLuint VBO;

		GLuint texture;

	public:
		Model3D(std::string modelFilename, TexInfo* texInfo, bool isNormalMapped);
		Model3D();

		~Model3D();
	
	private:
		void generateTexture(TexInfo* texInfo);
		void generateTextureWithNormalMap(TexInfo* texInfo);
		void initializeBuffers();

	public:
		void Draw();

	public:
		ObjData getObjData();
		Transform& getTransform();

};
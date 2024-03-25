#pragma once


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "../tiny_obj_loader.h"

#include <iostream>

/*Holds model data for Model3D*/
class ObjData {

	private:
		bool initialized;

	private:
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> material;
		tinyobj::attrib_t attributes;
		std::vector<GLfloat> fullVertexData;

	public:
		ObjData();

	public:
		void LoadModel(std::string filename);
		bool isInitialized();

	public:
		std::vector<tinyobj::shape_t> getShapes();
		std::vector<tinyobj::material_t> getMaterial();
		tinyobj::attrib_t getAttributes();
		std::vector<GLfloat> getfullVertexData();
			



};
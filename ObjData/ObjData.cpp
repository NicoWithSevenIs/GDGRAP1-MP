#include "ObjData.hpp"

ObjData::ObjData() : initialized(false) {}

void ObjData::LoadModel(std::string filename) {
    std::string warning, error;

    bool isInitialized = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        filename.c_str()
    );

    if (!warning.empty())
        std::cout << warning << std::endl;

    if (!error.empty()) {
        std::cout << error << std::endl;
        shapes.clear();
        material.clear();
        return;
    }

   
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {

        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        fullVertexData.push_back(this->attributes.vertices[vData.vertex_index * 3]);
        fullVertexData.push_back(this->attributes.vertices[vData.vertex_index * 3 + 1]);
        fullVertexData.push_back(this->attributes.vertices[vData.vertex_index * 3 + 2]);

        
        fullVertexData.push_back(this->attributes.normals[vData.normal_index * 3]);
        fullVertexData.push_back(this->attributes.normals[vData.normal_index * 3 + 1]);
        fullVertexData.push_back(this->attributes.normals[vData.normal_index * 3 + 2]);
        

        fullVertexData.push_back(this->attributes.texcoords[vData.texcoord_index * 2]);
        fullVertexData.push_back(this->attributes.texcoords[vData.texcoord_index * 2 + 1]);

    }

    

    this->initialized = true;

}

bool ObjData::isInitialized() {
    return this->initialized;
}

std::vector<tinyobj::shape_t>  ObjData::getShapes() {
    return this->shapes;
}

std::vector<tinyobj::material_t>  ObjData::getMaterial() {
    return this->material;
}

tinyobj::attrib_t  ObjData::getAttributes() {
    return this->attributes;
}

std::vector<GLfloat>  ObjData::getfullVertexData() {
    return this->fullVertexData;
}


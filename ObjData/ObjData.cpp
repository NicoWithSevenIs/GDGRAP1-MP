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

void ObjData::LoadPlayer(std::string filename) {
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

    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    for (int i = 0; i < shapes[0].mesh.indices.size(); i += 3) {
        tinyobj::index_t vData1 = shapes[0].mesh.indices[i];
        tinyobj::index_t vData2 = shapes[0].mesh.indices[i + 1];
        tinyobj::index_t vData3 = shapes[0].mesh.indices[i + 2];


        glm::vec3 v1 = glm::vec3(
            attributes.vertices[vData1.vertex_index * 3],
            attributes.vertices[(vData1.vertex_index * 3) + 1],
            attributes.vertices[(vData1.vertex_index * 3) + 2]
        );

        glm::vec3 v2 = glm::vec3(
            attributes.vertices[vData2.vertex_index * 3],
            attributes.vertices[(vData2.vertex_index * 3) + 1],
            attributes.vertices[(vData2.vertex_index * 3) + 2]
        );

        glm::vec3 v3 = glm::vec3(
            attributes.vertices[vData3.vertex_index * 3],
            attributes.vertices[(vData3.vertex_index * 3) + 1],
            attributes.vertices[(vData3.vertex_index * 3) + 2]
        );

        glm::vec2 uv1 = glm::vec2(
            attributes.texcoords[(vData1.texcoord_index * 2)],
            attributes.texcoords[(vData1.texcoord_index * 2) + 1]
        );

        glm::vec2 uv2 = glm::vec2(
            attributes.texcoords[(vData2.texcoord_index * 2)],
            attributes.texcoords[(vData2.texcoord_index * 2) + 1]
        );

        glm::vec2 uv3 = glm::vec2(
            attributes.texcoords[(vData3.texcoord_index * 2)],
            attributes.texcoords[(vData3.texcoord_index * 2) + 1]
        );


        glm::vec3 deltaPos1 = v2 - v1;
        glm::vec3 deltaPos2 = v3 - v1;


        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;


        float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));

        glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
    }

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {

        tinyobj::index_t vData = shapes[0].mesh.indices[i];
        /*mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );*/

        fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
        fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 2]);

        fullVertexData.push_back(attributes.normals[vData.normal_index * 3]);
        fullVertexData.push_back(attributes.normals[vData.normal_index * 3 + 1]);
        fullVertexData.push_back(attributes.normals[vData.normal_index * 3 + 2]);

        fullVertexData.push_back(attributes.texcoords[vData.texcoord_index * 2]);
        fullVertexData.push_back(attributes.texcoords[vData.texcoord_index * 2 + 1]);


        fullVertexData.push_back(tangents[i].x);
        fullVertexData.push_back(tangents[i].y);
        fullVertexData.push_back(tangents[i].z);

        fullVertexData.push_back(bitangents[i].x);
        fullVertexData.push_back(bitangents[i].y);
        fullVertexData.push_back(bitangents[i].z);
    }



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


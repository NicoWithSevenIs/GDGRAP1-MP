#pragma once

#include "Model3D.hpp"
/*Aids in handling the 3D Model*/
Model3D::Model3D(std::string modelFilename, TexInfo* texInfo){

    this->texture = *texInfo->getTexture();

    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    switch (texInfo->getColorChannels()) {
    case 3:
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            texInfo->getWidth(), 
            texInfo->getHeight(),
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            texInfo->getTexBytes()
        );
        break;
    case 4:
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            texInfo->getWidth(),
            texInfo->getHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            texInfo->getTexBytes()
        );
        break;
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    this->modelInfo.LoadModel(modelFilename);
    this->initializeBuffers();
}

void Model3D::initializeBuffers() {
    glGenVertexArrays(1, &this->VAO); 
    glGenBuffers(1, &this->VBO); 
}

Model3D::~Model3D() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

ObjData Model3D::getObjData(){return this->modelInfo;}
Transform& Model3D::getTransform(){return this->transform;}

//Bind Vertex Objects -> Draw -> Unbind -> Rinse and Repeat
void Model3D::Draw() {
   
    GLintptr normPtr = 3 * sizeof(float);
    GLintptr uvptr = 6 * sizeof(float);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO); 

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * this->modelInfo.getfullVertexData().size(),
        this->modelInfo.getfullVertexData().data(), 
        GL_DYNAMIC_DRAW); 

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normPtr); // 5 for 5 vertices (X,Y,Z,U,V)
    glEnableVertexAttribArray(1);

    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) uvptr );

    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    auto modelShader = ShaderManager::getModelShader();

    GLuint tex0Address = glGetUniformLocation(*modelShader, "tex0");
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(tex0Address, 0);

    unsigned int transformLoc = glGetUniformLocation(*modelShader, "transform");

    glm::mat4 transformMatrix = this->transform.getTransformMatrix();
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));

    glUseProgram(*modelShader);

    glBindVertexArray(this->VAO);

    glDrawArrays(GL_TRIANGLES, 0, this->modelInfo.getfullVertexData().size()/8);

    glBindVertexArray(0);

}


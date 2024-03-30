#pragma once

#include "Model3D.hpp"
/*Aids in handling the 3D Model*/
Model3D::Model3D(std::string modelFilename, TexInfo* texInfo, bool isNormalMapped){

    if (isNormalMapped) {
        this->generateTextureWithNormalMap(texInfo);
        this->modelInfo.LoadPlayer(modelFilename);
        this->initializeBuffers();
    }
    else {
        this->generateTexture(texInfo);
        this->modelInfo.LoadModel(modelFilename);
        this->initializeBuffers();
    }

}

void Model3D::generateTexture(TexInfo* texInfo) {
    //this->texture = *texInfo->getTexture();

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
}

void Model3D::generateTextureWithNormalMap(TexInfo * texInfo) {

    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texInfo->getWidth(), texInfo->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texInfo->getTexBytes());

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texInfo->getTexBytes());

        
    glGenTextures(1, &this->normTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->normTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texInfo->getWidth2(), texInfo->getHeight2(), 0, GL_RGB, GL_UNSIGNED_BYTE, texInfo->getNormalBytes());

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texInfo->getNormalBytes());
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

    auto modelShader = ShaderManager::getModelShader2();

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

void Model3D::DrawNormalMapped() {

    auto modelShader = ShaderManager::getModelShader();

    GLintptr normPtr = 3 * sizeof(float);
    GLintptr uvptr = 6 * sizeof(float);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * this->modelInfo.getfullVertexData().size(),
        this->modelInfo.getfullVertexData().data(),
        GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (void*)normPtr); // 5 for 5 vertices (X,Y,Z,U,V)
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (void*)uvptr);

    glEnableVertexAttribArray(2);

    GLintptr  tangentPtr = 8 * sizeof(float);
    GLintptr bitangentPtr = 11 * sizeof(float);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (void*)tangentPtr);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (void*)bitangentPtr);
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glActiveTexture(GL_TEXTURE0);
    GLuint tex0Loc = glGetUniformLocation(*modelShader, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(tex0Loc, 0);

    glActiveTexture(GL_TEXTURE1);
    GLuint tex1Loc = glGetUniformLocation(*modelShader, "norm_tex");
    glBindTexture(GL_TEXTURE_2D, this->normTexture);
    glUniform1i(tex1Loc, 1);

    unsigned int transformLoc = glGetUniformLocation(*modelShader, "transform");

    glm::mat4 transformMatrix = this->transform.getTransformMatrix();
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));

    glUseProgram(*modelShader);

    glBindVertexArray(this->VAO);

    glDrawArrays(GL_TRIANGLES, 0, this->modelInfo.getfullVertexData().size() / 14);

    glBindVertexArray(0);
}
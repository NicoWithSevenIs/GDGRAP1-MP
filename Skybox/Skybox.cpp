#include "Skybox.hpp"
#include "../Utilities.h"
Skybox::Skybox(TexInfo texture): texInfo(texture) {
    Utils::Log("Yo");
}


void Skybox::initialize() {
   
    glGenTextures(1, &this->skyboxTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    std::vector<unsigned char*>* vecDatas = texInfo.getSkyboxDatas();
    std::vector<int> vecWidths = texInfo.getVecWidth();
    std::vector<int> vecHeights = texInfo.getVecHeight();
    std::vector<int> vecColorChannels = texInfo.getVecColorChannels();

    std::cout << vecDatas->size() << std::endl;

    for (int i = 0; i < 6; i++) {
        if ((*vecDatas)[i]) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, vecWidths[i], vecHeights[i], 0, GL_RGB, GL_UNSIGNED_BYTE, (*vecDatas)[i]);
            stbi_image_free((*vecDatas)[i]);
        }
        else {
            std::cout << "Failed to load texture!" << std::endl;
        }
    }

    stbi_set_flip_vertically_on_load(true);

    this->initializeBuffers();
}

void Skybox::initializeBuffers() {

    float skyboxVertices[]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    //Skybox Indices
    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
}

void Skybox::Draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

    auto skyboxShader = ShaderManager::getSkyboxShader();
    auto modelShader = ShaderManager::getModelShader();

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glUseProgram(*skyboxShader);

    glm::mat4 sky_view = glm::mat4(1.f);
    sky_view = glm::mat4(glm::mat3(viewMatrix));

    unsigned int skyboxViewLoc = glGetUniformLocation(*skyboxShader, "view");
    glUniformMatrix4fv(skyboxViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));

    unsigned int skyboxProjLoc = glGetUniformLocation(*skyboxShader, "projection");
    glUniformMatrix4fv(skyboxProjLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(this->VAO);
  
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glUseProgram(*modelShader);
}
#include "ShaderManager.hpp"
#include "../Utilities.h"

/*.Cpp file holds all the glfw methods for the shader*/
ShaderManager::ShaderManager() {
    this->shaders["Model"] = nullptr;
    this->shaders["Skybox"] = nullptr;
}

ShaderManager::~ShaderManager() {
    for (auto i : this->shaders) {
        if(i.second)
            delete i.second;
    }
}

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager* ShaderManager::getInstance() {
    if(!instance)
        instance = new ShaderManager();
    return instance;
}

void ShaderManager::LoadShader(std::string key, std::string path, unsigned int shader_type) {

    std::fstream shaderSrc(path);

    if (!shaderSrc.is_open()) {
        Utils::Log("Failed to open file");
    }

    std::stringstream shaderBuff;
    shaderBuff << shaderSrc.rdbuf();

    std::string shaderS = shaderBuff.str();
    const char* s = shaderS.c_str();

    //Initializing Shaders
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &s, NULL);
    glCompileShader(shader);

    if(!this->shaders[key])
        this->shaders[key] = new GLuint(glCreateProgram());
   
    glAttachShader(*this->shaders[key], shader);

    this->LoadSkyboxShader();

}

void ShaderManager::LoadSkyboxShader() {

    std::fstream skyboxVertSrc("Shaders/skybox.vert");
    std::stringstream skyBoxVertBuff;
    skyBoxVertBuff << skyboxVertSrc.rdbuf();

    std::string skyBoxVertS = skyBoxVertBuff.str();
    const char* sky_v = skyBoxVertS.c_str();

    std::fstream skyboxFragSrc("Shaders/skybox.frag");
    std::stringstream skyboxFragBuff;
    skyboxFragBuff << skyboxFragSrc.rdbuf();

    std::string sky_fragS = skyboxFragBuff.str();
    const char* sky_f = sky_fragS.c_str();

    GLuint skyboxVertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(skyboxVertShader, 1, &sky_v, NULL);
    glCompileShader(skyboxVertShader);

    GLuint skyboxFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(skyboxFragShader, 1, &sky_f, NULL);
    glCompileShader(skyboxFragShader);

    GLuint skyboxShaderProg = glCreateProgram();
    glAttachShader(skyboxShaderProg, skyboxVertShader);
    glAttachShader(skyboxShaderProg, skyboxFragShader);

}

void ShaderManager::LoadShaders() {
   
    auto i = getInstance();

    i->LoadShader("Model", "Shaders/shaders.vert", GL_VERTEX_SHADER);
    i->LoadShader("Model", "Shaders/shaders.frag", GL_FRAGMENT_SHADER);

    glLinkProgram(*getModelShader());

    i->LoadShader("Model", "Shaders/skybox.vert", GL_VERTEX_SHADER);
    i->LoadShader("Model", "Shaders/skybox.frag", GL_FRAGMENT_SHADER);

    glLinkProgram(*getSkyboxShader());
}

GLuint* ShaderManager::getModelShader() {
    return getInstance()->shaders["Model"];
}

unsigned int* ShaderManager::getSkyboxShader() {
    return &getInstance()->skyboxShader;
}


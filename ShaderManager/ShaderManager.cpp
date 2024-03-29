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

    std::cout << "Currently loading: " << key << std::endl;

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

}

void ShaderManager::LoadShaders() {
   
    auto i = getInstance();

    i->LoadShader("Model", "Shaders/shaders.vert", GL_VERTEX_SHADER);
    i->LoadShader("Model", "Shaders/shaders.frag", GL_FRAGMENT_SHADER);

    glLinkProgram(*getModelShader());

    i->LoadShader("Skybox", "Shaders/skybox.vert", GL_VERTEX_SHADER);
    i->LoadShader("Skybox", "Shaders/skybox.frag", GL_FRAGMENT_SHADER);

    glLinkProgram(*getSkyboxShader());

}

GLuint* ShaderManager::getModelShader() {
    return getInstance()->shaders["Model"];
}

GLuint* ShaderManager::getSkyboxShader() {
    return getInstance()->shaders["Skybox"];
}

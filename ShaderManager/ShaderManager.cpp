#include "ShaderManager.hpp"


/*.Cpp file holds all the glfw methods for the shader*/
ShaderManager::ShaderManager() {
    this->shaderProg = NULL;
}

ShaderManager::~ShaderManager() {
    if (this->shaderProg)
        delete shaderProg;
}

void ShaderManager::LoadShader(std::string path, unsigned int shader_type) {

    std::fstream shaderSrc(path);

    std::stringstream shaderBuff;
    shaderBuff << shaderSrc.rdbuf();

    std::string shaderS = shaderBuff.str();
    const char* s = shaderS.c_str();

    //Initializing Shaders
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &s, NULL);
    glCompileShader(shader);

    if (!this->shaderProg) {
        this->shaderProg = new GLuint(glCreateProgram());
    }

    glAttachShader(*this->shaderProg, shader);

}

GLuint* ShaderManager::getShaderProg() { return this->shaderProg; }

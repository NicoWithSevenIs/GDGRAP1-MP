#include "OrthographicCamera.hpp"


Orthographic::Orthographic(glm::vec3 cameraPos, glm::vec3 cameraFront, OrthoData orthoData):
	Camera(cameraPos, cameraFront), orthoData(orthoData)
{}

void Orthographic::Draw(ShaderManager& shader){
    
    Camera::Draw(shader);

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projectionMatrix = glm::ortho(
         this->orthoData.left,
         this->orthoData.right,
         this->orthoData.bottom,
         this->orthoData.top,
         this->orthoData.znear,
         this->orthoData.zfar
     );
 
    unsigned int projectionLoc = glGetUniformLocation(*shader.getShaderProg(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(*shader.getShaderProg(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}
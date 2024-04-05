#version 330 core

out vec4 FragColor;

in vec3 texCoord;

uniform samplerCube skybox;

uniform int isTinted;

void main() {
	
	if (isTinted == 0) {
		FragColor = texture(skybox, texCoord) * vec4(1.0f, 1.0f, 1.0f, 0.0f);
	}
	else if (isTinted == 1) {
		FragColor = texture(skybox, texCoord) * vec4(0.0f, 1.0f, 0.0f, 0.0f);
	}
	
}
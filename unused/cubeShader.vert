#version 330 core
	
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Uniform variables can be updated by fetching their location and passing values to that location
uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 model;


// Outputs of the vertex shader are the inputs of the same name of the fragment shader.
// The default output, gl_Position, should be assigned something. You can define as many
// extra outputs as you need.
//out float sampleExtraOutput;
out vec3 Normal;
//out vec3 FragPos;

void main()
{
    // OpenGL maintains the D matrix so you only need to multiply by P, V (aka C inverse), and M
    gl_Position = projection * modelview * vec4(position.x/1.0f, position.y/1.0f, position.z/1.0f, 1.0);
    Normal = mat3(transpose(inverse(model))) * normal;
}
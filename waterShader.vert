#version 330 core
// NOTE: Do NOT use any version older than 330! Bad things will happen!

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec3 position;

// Uniform variables can be updated by fetching their location and passing values to that location
uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 model;
uniform vec3 cameraPosition;

out vec2 TexCoords;
out vec4 clipSpace;
out vec3 toCamVector;

//clipping plane
//uniform vec4 plane;

const float tiling = 6.0;

// Outputs of the vertex shader are the inputs of the same name of the fragment shader.
// The default output, gl_Position, should be assigned something. You can define as many
// extra outputs as you need.


void main()
{

    vec4 worldPosition = model * vec4(position,1.0);
    
    TexCoords = vec2(position.x/20.0+0.5, position.z/20.0+0.5)*tiling;
    // OpenGL maintains the D matrix so you only need to multiply by P, V (aka C inverse), and M
    clipSpace = projection * modelview * vec4(position.x,position.y,position.z,1.0);
    gl_Position = clipSpace;

    toCamVector = cameraPosition - worldPosition.xyz;
}

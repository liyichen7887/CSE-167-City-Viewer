#version 330 core
in vec2 Texcoord;
out vec4 outColor;
uniform int numOfSample;
uniform sampler2D texFramebuffer0;
uniform sampler2D texFramebuffer1;
uniform sampler2D texFramebuffer2;
uniform sampler2D texFramebuffer3;
uniform sampler2D texFramebuffer4;
uniform sampler2D texFramebuffer5;
uniform sampler2D texFramebuffer6;
uniform sampler2D texFramebuffer7;
uniform sampler2D texFramebuffer8;

void main(){
	float s = float(numOfSample);
	outColor = texture(texFramebuffer0, Texcoord) * (0.05f) + 
	texture(texFramebuffer1, Texcoord) * (0.05f) +
	texture(texFramebuffer2, Texcoord) * (0.1f) +
	texture(texFramebuffer3, Texcoord) * (0.15f) +
	texture(texFramebuffer4, Texcoord) * (0.3f) +
	texture(texFramebuffer5, Texcoord) * (0.15f) +
	texture(texFramebuffer6, Texcoord) * (0.1f) +
	texture(texFramebuffer7, Texcoord) * (0.05f) +
	texture(texFramebuffer8, Texcoord) * (0.05f)
	;	
	outColor.a = 1.0;	
}

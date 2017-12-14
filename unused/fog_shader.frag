#version 330 core
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texFramebuffer;
uniform sampler2D tDepth;
uniform float width;
uniform float height;
uniform int openFOG;



void main(){
	vec4 testColor = texture(texFramebuffer, Texcoord);	
	
    vec2 aspectcorrect = vec2( 1.0, 16.0f / 9.0f );
	vec4 depth1 = texture2D(tDepth, Texcoord );
    float z_n = 2.0 * depth1.x - 1.0;
    float z_e = 2.0 * 0.1 * 1000 / (1000 + 0.1 - z_n * (1000 - 0.1));

	outColor = vec4(0.5f,0.5f,0.5f,0.0f);
	if (openFOG == 1){
		outColor.a = 1.0f * z_e/600.0f;
	}	
	
}

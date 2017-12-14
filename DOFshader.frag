#version 330 core
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texFramebuffer;
uniform sampler2D tDepth;
uniform float width;
uniform float height;
uniform int openDOF;
uniform float focus;
uniform int openFOG;

vec4 dof(vec4 col, vec2 aspectcorrect, vec2 dofblur){    
    vec2 dofblur9 = dofblur * 0.5;
    vec2 dofblur7 = dofblur * 0.3;
    vec2 dofblur4 = dofblur * 0.1;
	
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.0f, 0.4f ) * aspectcorrect ) * dofblur );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.15, 0.37 ) * aspectcorrect ) * dofblur );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.29, 0.29 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.37, 0.15 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.40, 0.0 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.37, -0.15 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.29, -0.29 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.15, -0.37 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.0, -0.4 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.15, 0.37 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.29, 0.29 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.37, 0.15 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.4, 0.0 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.37, -0.15 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.29, -0.29 ) * aspectcorrect ) * dofblur );
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.15, -0.37 ) * aspectcorrect ) * dofblur );
	
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.15, 0.37 ) * aspectcorrect ) * dofblur9 );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.37, 0.15 ) * aspectcorrect ) * dofblur9 );
    col += texture( texFramebuffer, Texcoord + ( vec2( 0.37, -0.15 ) * aspectcorrect ) * dofblur9 );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.15, -0.37 ) * aspectcorrect ) * dofblur9 );
    col += texture( texFramebuffer, Texcoord + ( vec2( -0.15, 0.37 ) * aspectcorrect ) * dofblur9 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.37, 0.15 ) * aspectcorrect ) * dofblur9 );
	col += texture( texFramebuffer, Texcoord + ( vec2( -0.37, -0.15 ) * aspectcorrect ) * dofblur9 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.15, -0.37 ) * aspectcorrect ) * dofblur9 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.29, 0.29 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.40, 0.0 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.29, -0.29 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.0, -0.4 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( -0.29, 0.29 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( -0.4, 0.0 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( -0.29, -0.29 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.0, 0.4 ) * aspectcorrect ) * dofblur7 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.29, 0.29 ) * aspectcorrect ) * dofblur4 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.4, 0.0 ) * aspectcorrect ) * dofblur4 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.29, -0.29 ) * aspectcorrect ) * dofblur4 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.0, -0.4 ) * aspectcorrect ) * dofblur4 );
	col += texture( texFramebuffer, Texcoord + ( vec2( -0.29, 0.29 ) * aspectcorrect ) * dofblur4 );
	col += texture( texFramebuffer, Texcoord + ( vec2( -0.4, 0.0 ) * aspectcorrect ) * dofblur4 );
	col += texture( texFramebuffer, Texcoord + ( vec2( -0.29, -0.29 ) * aspectcorrect ) * dofblur4 );
	col += texture( texFramebuffer, Texcoord + ( vec2( 0.0, 0.4 ) * aspectcorrect ) * dofblur4 );
	
    return col/ 41.0;
}
void main(){
	vec4 testColor = texture(texFramebuffer, Texcoord);	
	
    vec2 aspectcorrect = vec2( 1.0, 16.0f / 9.0f );
	vec4 depth1 = texture2D(tDepth, Texcoord );
    float z_n = 2.0 * depth1.x - 1.0;
    float z_e = 2.0 * 0.1 * 1000 / (1000 + 0.1 - z_n * (1000 - 0.1));
    float factor = z_e - focus;
    
    vec2 dofblur = vec2 ( clamp( factor* 1.0f/9.0f/(1000 - 0.1), -0.02f, 0.02f ));
    //vec2 dofblur =vec2 ( factor* 1.0f/5.6f / 666);

    vec4 col = vec4( 0.0f );
    col += texture(texFramebuffer, Texcoord);
	if (openDOF == 1){
		col = dof(col, aspectcorrect, dofblur);
	}	
	outColor = col;
	if (openFOG == 1){
		float fog_den = sqrt(sqrt(z_e/600.0f));
		if (fog_den >= 1.0f){
			fog_den = 1.0f;
		}
		outColor = mix(outColor, vec4(0.5, 0.5, 0.5, 1.0), fog_den);

	}	
	outColor.a = 1.0;	
}

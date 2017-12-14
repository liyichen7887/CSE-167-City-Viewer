
#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.


//uniform vec4 color_in;
in vec2 TexCoords;
in vec4 clipSpace;
in vec3 toCamVector;

//The first vec4 type output determines the color of the fragment
//write in the render target 0
layout(location = 0) out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudv;

uniform float moveFactor;

const float waveStr = 0.02; //how much for the du/dv distortion effect

void main()
{
    vec2 ndc = ((clipSpace.xy/clipSpace.w)+1)/2;
    vec2 refractionTexCoords = vec2(ndc.x,ndc.y);
    vec2 reflecTexCoords = vec2(ndc.x,-ndc.y);

    //distortion with du/dv map, map from 0-1 to -1 - 1, used as offset
    vec2 distortion1 = texture(dudv, vec2(TexCoords.x + moveFactor*4, TexCoords.y)).rg * 2.0 - 1.0;
    //dynamic distortion
    vec2 distortion2 = texture(dudv, vec2(-TexCoords.x + moveFactor*4, TexCoords.y + moveFactor*4)).rg * 2.0 - 1.0;
    //more realistic
    vec2 totalDistortion = distortion1 + distortion2;
    totalDistortion *= waveStr;
    reflecTexCoords+=totalDistortion;
    refractionTexCoords+=totalDistortion;
    
    //avoid margin glitches
    refractionTexCoords = clamp(refractionTexCoords, 0.001, 0.999);
    reflecTexCoords.x = clamp(reflecTexCoords.x, 0.001, 0.999);
    reflecTexCoords.y = clamp(reflecTexCoords.y, -0.999, -0.001);
    
    vec4 reflectionColor = texture(reflectionTexture,reflecTexCoords);
    vec4 refractionColor = texture(refractionTexture,refractionTexCoords);

//    vec4 reflectionColor = texture(reflectionTexture,TexCoords);
//    vec4 refractionColor = texture(refractionTexture,TexCoords);
    
    vec3 viewVector = normalize(toCamVector);
    float refractiveFactor = dot(viewVector,vec3(0.0,1.0,0.0));
    //adjust for less reflection
    refractiveFactor = pow(refractiveFactor,0.9);
    
    //color = refractionColor;
    //color = reflectionColor;
    //color = vec4(1.0,0.0,0.5,1.0);
    
    color = mix(reflectionColor,refractionColor,refractiveFactor);
    color = mix(color, vec4(0.0, 0.2, 0.4, 1.0), 0.3);      //make a little bit bluer
	//color = reflectionColor;
	//color = vec4(1,0,0,1);
}


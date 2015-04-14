#ifdef GL_ES
precision lowp float; 
varying mediump vec2 v_texCoord;
#else
varying vec2 v_texCoord;
#endif


uniform vec2 resolution;
uniform vec4 startColor;
uniform vec4 endColor;

void main(void)
{

	float maxRadius = resolution.y/2.0;

	
    float distanceFromLight = length(v_texCoord - resolution/4.0);


	distanceFromLight /= sin(CC_Time+1.5707)*maxRadius/2.0+maxRadius;
    gl_FragColor = mix(startColor, endColor, distanceFromLight);
}


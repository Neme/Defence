#ifdef GL_ES
precision lowp float; 
varying mediump vec4 v_color;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_color;
varying vec2 v_texCoord;
#endif


uniform vec2 packetSize;

void main(void)
{
	float maxRadius = packetSize.y/8.0;
	float falloff = 0.2;
	
	float distanceFromLight = length(v_texCoord - packetSize/4.0);
	
	distanceFromLight /= maxRadius;
	distanceFromLight = (1.0/pow(distanceFromLight,3.0) - 0.23) * falloff;

	
	vec4 out_color = v_color;
	out_color = mix(vec4(0.5,0.5,0.5,0.0),out_color, distanceFromLight);

	
	
	
    gl_FragColor = out_color;
}


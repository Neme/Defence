#ifdef GL_ES
precision lowp float; 
varying mediump vec4 v_color;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_color;
varying vec2 v_texCoord;
#endif


uniform vec2 towerSize;
uniform float pulseTime;


void main(void)
{
	float maxRadius = towerSize.y / (sin(CC_Time.x*pulseTime) * 0.5 + 7.0);
	float falloff = 0.2;
	
	float distanceFromLight = length(v_texCoord - towerSize/4.0);
	
	distanceFromLight /= maxRadius;
	distanceFromLight = (1.0/pow(distanceFromLight,3.0) - 0.23) * falloff;

	
	
	
	vec4 out_color = v_color;
	
	if(out_color.r == out_color.g) {
		out_color.a = distanceFromLight;
	} else {
		vec4 mixCol = vec4(0.0,0.0,0.0,0.0);
		out_color = mix(mixCol,out_color, distanceFromLight);
	}
	

	
	
	
    gl_FragColor = out_color;
}


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
uniform int drawMode;

void main(void)
{
	vec4 out_color = v_color;
	
	if(drawMode == 0) {
		float maxRadius = towerSize.y / (sin(CC_Time.x* (0.1/pulseTime + 20.0f) ) * 0.5 + 7.0);
		float falloff = 0.2;
		
		float distanceFromLight = length(v_texCoord - towerSize/4.0);
		
		distanceFromLight /= maxRadius;
		distanceFromLight = (1.0/pow(distanceFromLight,3.0) - 0.23) * falloff;
		
		
		
		if(out_color.r == out_color.g) {
			out_color.a = distanceFromLight;
		} else {
			vec4 mixCol = vec4(0.0,0.0,0.0,0.0);
			out_color = mix(mixCol,out_color, distanceFromLight);
		}
		
	} else if(drawMode == 1) {
		float maxRadius = towerSize.y / (sin(CC_Time.x* (0.1/pulseTime + 20.0f) ) * 0.5 + 7.0);
		float falloff = 0.2;
		
		float distanceFromLight = length(v_texCoord - towerSize/4.0);
		
		distanceFromLight /= maxRadius;
		distanceFromLight = (1.0/pow(distanceFromLight,3.0) - 0.23) * falloff;

		vec4 mixCol = out_color / 1.1;
		mixCol.a = 0.0;
		out_color = mix(mixCol,out_color, distanceFromLight);
	}
	
	
    gl_FragColor = out_color;
}


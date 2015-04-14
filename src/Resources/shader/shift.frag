#ifdef GL_ES
precision lowp float; 
varying mediump vec2 v_texCoord;
varying mediump vec4 v_fragmentColor;
#else
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
#endif

uniform vec2 resolution;
uniform float blurRadius;
uniform float sampleNum;


vec4 blur(vec2 p)
{
    if (blurRadius > 0.0 && sampleNum > 1.0)
    {
        vec4 col = vec4(0);
        vec2 unit = 1.0 / resolution.xy;
        
        float r = blurRadius;
        float sampleStep = r / sampleNum;
        
        float count = 0.0;
        
        for(float x = -r; x < r; x += sampleStep)
        {
            for(float y = -r; y < r; y += sampleStep)
            {
                float weight = (r - abs(x)) * (r - abs(y));
                col += texture2D(CC_Texture0, p + vec2(x * unit.x, y * unit.y)).rgba * weight;
                count += weight;
            }
        }
        
        return col / count;
    }
    
    return texture2D(CC_Texture0, p).rgba;
}

vec4 grad(vec2 p) {
	vec2 u_c = vec2(0.5,0.5);
	
	float distanceFromLight = length(p - u_c);
	distanceFromLight = (1.0/pow(distanceFromLight,3.0) - 0.23) * 0.05;

	return mix(vec4(0.0,0.0,0.0,1.0),vec4(1.0,1.0,1.0,1.0), distanceFromLight);
}

void main(void)
{
	vec4 blur = blur(v_texCoord);
	vec4 rad = grad(v_texCoord);
	

	gl_FragColor = mix(blur,texture2D(CC_Texture0, v_texCoord), clamp(rad.r,0.0,1.0));
}


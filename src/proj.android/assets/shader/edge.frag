#ifdef GL_ES

varying mediump vec4 v_color;
varying mediump vec2 v_texcoord;
#else
varying vec4 v_color;
varying vec2 v_texcoord;
#endif

void main()
{
	gl_FragColor = v_color*step(0.0, 1.0 - length(v_texcoord));
}
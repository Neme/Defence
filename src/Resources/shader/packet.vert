#ifdef GL_ES
attribute mediump vec4 a_position;
attribute mediump vec4 a_color;
attribute mediump vec2 a_texCoord;

varying mediump vec2 v_texCoord;
varying mediump vec4 v_color;

#else
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;
varying vec4 v_color;
#endif



void main()
{
	v_color = vec4(a_color.rgb * a_color.a, a_color.a);
    gl_Position = CC_PMatrix * a_position;
    v_texCoord = a_texCoord;
}

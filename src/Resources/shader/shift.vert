#ifdef GL_ES
attribute mediump vec4 a_position;
attribute mediump vec2 a_texCoord;

varying mediump vec2 v_texCoord;
varying mediump vec4 v_color;

#else
attribute vec4 a_position;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;
varying vec4 v_color;
#endif

void main()
{
    gl_Position = CC_PMatrix * a_position;
    v_texCoord = a_texCoord;
}

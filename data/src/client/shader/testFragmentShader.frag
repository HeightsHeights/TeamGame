#version 120
 varying vec3 outcolor;

void main(void)
{
    gl_FragColor.xyz = outcolor;
    gl_FragColor.w = 1.0;
}
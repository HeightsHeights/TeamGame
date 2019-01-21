attribute vec3 position;
attribute vec3 position;
attribute vec2 uv;

uniform vec2 u_resolution;
varying vec2 vuv;

void main(void)
{
    //gl_Position = mul(gl_ProjectionMatrix,mul(gl_ModelViewProjectionMatrix,vec4(0,0,0,1))+vec4(2.0 / 1280.0, 2.0 / 720.0, 1.0, 1.0)*vec4(position,0));

    vuv = uv;
}
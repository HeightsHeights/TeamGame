attribute vec3 position;
attribute vec2 uv;

uniform vec2 u_resolution;

varying vec2 vuv;
void main(void){

    gl_Position = vec4(2.0 / 1280.0, 2.0 / 720.0, 1.0, 1.0) * (gl_ModelViewMatrix * vec4(position, 1.0));
    vuv = uv;
}
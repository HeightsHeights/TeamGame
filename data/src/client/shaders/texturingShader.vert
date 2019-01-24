attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;
varying vec2 vuv;
void main(void){
    
    gl_Position = gl_ModelViewMatrix * vec4(position,1.0);
    vuv = uv;
}
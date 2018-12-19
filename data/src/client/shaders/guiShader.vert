attribute vec3 position;
attribute vec2 uv;

varying vec2 vuv;
void main(void){

    gl_Position = vec4(1.0 / 16.0, 1.0/ 9.0, 1.0, 1.0) * vec4(position,1.0);
    vuv = uv;
}
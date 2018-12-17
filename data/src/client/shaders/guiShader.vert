attribute vec3 position;
attribute vec4 color;
void main(void){
    gl_FrontColor = color;
    gl_Position = vec4(position, 1.0);
}
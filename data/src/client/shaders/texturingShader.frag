varying vec2 vuv;
uniform sampler2D texture;
vec4 color;
void main(void){

    color = texture2D(texture, vuv);

    gl_FragColor = color;
}
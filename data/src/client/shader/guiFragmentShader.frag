varying vec2 vuv;
uniform sampler2D texture;
void main(void){
    gl_FragColor = texture2D(texture, vuv);
}
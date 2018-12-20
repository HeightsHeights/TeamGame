varying vec2 vuv;

uniform sampler2D texture;
void main(void){
    vec4 color = texture2D(texture, vuv);
    gl_FragColor = color;
}
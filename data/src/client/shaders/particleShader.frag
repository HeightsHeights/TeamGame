varying vec2 vuv;
uniform sampler2D texture;
uniform float brightness;
void main(void)
{
        // vec4 color = texture2D(texture, vuv) * vec4(brightness, brightness, brightness, 1.0);
        vec4 color = vec4(1.0,0.0,0.0,1.0) * vec4(brightness, brightness, brightness, 1.0);
        gl_FragColor = color;
}

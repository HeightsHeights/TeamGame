varying vec3 outcolor;
varying vec2 vuv;
uniform sampler2D texture;
vec4 color;
uniform float zaz;

void main(void)
{
    if(vuv.x < 1.0 && vuv.x >0.0 && vuv.y < 1.0 && vuv.y > 0.0 ){
        color = texture2D(texture, vuv);
        gl_FragColor.xyz = color.xyz;
        gl_FragColor.w = 0.6;
    }
    else {
        gl_FragColor = vec4(1.0,0.0,0.0,zaz);
    }
}
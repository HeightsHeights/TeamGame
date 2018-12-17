attribute vec3 position;
attribute vec3 color;
varying vec3 outcolor;
void main(void)
{
    vec4 a = mul(gl_ProjectionMatrix,mul(gl_ModelViewProjectionMatrix,vec4(0,0,0,1))+vec4(position.x,position.y,0,0));
    outcolor = color;
    // 描画頂点位置
    gl_Position = a ;
}
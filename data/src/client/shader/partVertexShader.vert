attribute vec3 vertex;
attribute vec2 position;
attribute vec3 color;
attribute vec2 uv;
varying vec3 outcolor;
varying vec2 vuv;
void main(void)
{
    outcolor = color;
     mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                        position.x, position.y, 0, 1.0);
    // 描画頂点位置
    gl_Position = gl_ModelViewMatrix * matrix * vec4(vertex, 1.0);
    vuv = vec2(position.x/30 + uv.x , -position.y/30 + uv.y);
}
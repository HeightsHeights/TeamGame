attribute vec3 vertex;
attribute vec3 position;
attribute vec3 color;
varying vec3 outcolor;
void main(void)
{
    outcolor = color;
     mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                        position.x, position.y, position.z, 1.0);
    // 描画頂点位置
    gl_Position = gl_ModelViewMatrix * matrix * vec4(vertex, 1.0);
}
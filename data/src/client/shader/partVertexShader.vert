attribute vec3 vertex;
attribute vec2 position;
attribute vec3 color;
attribute vec2 uv;
varying vec3 outcolor;
varying vec2 vuv;
vec2 uopo;
void main(void)
{
    outcolor = color;
    
     mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                        position.x, position.y, 0, 1.0);
    vec4 b = matrix * vec4(vertex, 1.0);                    
    // 描画頂点位置
    vec4 a = mul(gl_ProjectionMatrix,mul(gl_ModelViewProjectionMatrix,vec4(0,0,0,1))+vec4(1.0/1.7,1.0,1.0,1.0)* b );
    // gl_Position = gl_ModelViewMatrix * matrix * vec4(vertex, 1.0);
    gl_Position = a;
    uopo = vec2(position.x/45.0  + uv.x , -position.y/45.0  + uv.y);
    
    vuv = uopo;
}
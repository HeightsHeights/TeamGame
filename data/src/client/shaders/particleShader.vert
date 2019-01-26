attribute vec3 vertex;
attribute vec2 uv;
attribute vec3 position;
varying vec2 vuv;
void main(void)
{
    mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                        position.x, position.y, position.z, 1.0);
    vec4 b = matrix * vec4(vertex, 1.0);       
    // 描画頂点位置
    // gl_Position =  gl_ProjectionMatrix * ( ( gl_ModelViewProjectionMatrix * vec4(0,0,0,1) ) + vec4(1.0/1.7,1.0,1.0,1.0)* b  );
    // uopo = vec2(position.x/45.0  + uv.x , -position.y/45.0  + uv.y);
    vuv = uv;
    gl_Position =gl_ModelViewMatrix * b;
}
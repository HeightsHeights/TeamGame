attribute vec3 position;
attribute vec2 uv;
varying vec3 vPos;
varying vec3 vNrm;
varying vec2 vuv;
void main(void){
        //頂点位置と法線
    vPos = position;
    // vPos = gl_Vertex.xyz;
    vNrm = gl_NormalMatrix*gl_Normal;

    gl_Position = gl_ModelViewMatrix * vec4(position,1.0);
    vuv = uv;
}
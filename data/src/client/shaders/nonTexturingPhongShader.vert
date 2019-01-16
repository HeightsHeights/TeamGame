attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;
varying vec3 vPos;
varying vec3 vNrm;
varying vec2 vuv;

void main(void){
        //頂点位置と法線
    vPos = (gl_ModelViewMatrix * vec4(position,1.0)).xyz;
    // vPos = gl_Vertex.xyz;
    vNrm = normalize(gl_NormalMatrix * normal);

    gl_Position = gl_ModelViewMatrix * vec4(position,1.0);
    vuv = uv;
}
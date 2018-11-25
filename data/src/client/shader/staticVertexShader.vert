varying vec3 vPos;
varying vec3 vNrm;
 
void main(void)
{
    // 頂点位置と法線
    vPos = (gl_ModelViewMatrix*gl_Vertex).xyz;
    vNrm = gl_NormalMatrix*gl_Normal;
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MutiTexCoord0;
    // 描画頂点位置
    gl_Position = ftransform();
}
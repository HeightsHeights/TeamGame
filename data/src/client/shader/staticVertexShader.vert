varying vec4 position;
varying vec3 normal;

void main(void)
{
  vec4 position = gl_ModelViewMatrix * gl_Vertex;
  vec3 normal = normalize(gl_NormalMatrix * gl_Normal);

  gl_Position = ftransform();
}
attribute vec3 position;
attribute vec2 uv;

varying vec2 vuv;

void main(void)
{
    gl_Position =  gl_ProjectionMatrix * ( ( gl_ModelViewProjectionMatrix * vec4(0,0,0,1) ) + vec4(1.0/1.7,1.0,1.0,1.0)* vec4( position, 0 )  );
    vuv = uv;
}
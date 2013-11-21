
varying vec2 vUv;


varying float noise;
 

void main(){



    vec4 newVertex = gl_Vertex-vec4(3,0,0,1);
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * newVertex;

}
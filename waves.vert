varying vec3 vertex_color;
varying float NdotL;

uniform float time;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){

     float noise=rand(gl_Vertex.xy);
     
     float x0 = gl_Vertex.x;
     float y0 = gl_Vertex.y;
     
     float A = 0.5;
     float W = 10.0;     
     
     //basic summation waves     
     float x = A*sin(x0-W*time);
     float y = A*cos(y0-W*time);
     float hi = A*sin(x0-W*time)*cos(x0-2.0*W*time);
     float omg = A*cos(y0-W*time)*cos(y0-2.0*W*time)*cos(x0-W*time);
     float z = x+y+hi+omg;

     //v0 of Gerstner waves , k's are wave directions
     vec3 X_=gl_Vertex.xyz;
     vec3 k1=vec3(.5,.2,.3);
     vec3 k2=vec3(.3,-.1,0.3);
     
     float w1=9.0;
     float w2=17.0;
     float A1=.5;
     float A2=.7;
     
     //troll testing
     k1=vec3(.9,.7,-.3);// k1=normalize(k1);
     k2=vec3(.7,-.6,-.2);//k2=normalize(k2);
     w1=80.0; w2=100.0;  //   A2=.2;A1=.1;
     x=-(A1*sin(dot(k1,X_)-w1*time))*(A1*sin(dot(k1,X_)-w1*time));

     x=-(A1*sin(dot(k1,X_)-w1*time));
     x -= A2*sin(dot(k2,X_)-w2*time);
     y=A1*cos(dot(k1,X_)-w1*time);
     y+=A2*cos(dot(k2,X_)-w2*time);
     z=gl_Vertex.z;
     z+=x+y;
     
     x=gl_Vertex.x;
     y=gl_Vertex.y;
     vec4 newPos = vec4(x,y,z,1.0);

     vec3 normal = newPos.xyz; 
     if(normal.x < 0.0) normal.x = -normal.x;
     normal = normalize(normal);
     normal = cross(normal, vec3(0.0, 1.0, 0.0));
     vec3 lightDir = vec3(gl_LightSource[0].position);
     lightDir = normalize(lightDir);
     NdotL = max(dot(normal,lightDir), 0.0);

     
     vertex_color = gl_Color.xyz;
     //vertex_color = vec3(0.82, 0.78, 0.67); //sand color
     //vertex_color = vec3(0,0.3,0.5);     //ocean color
     gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * newPos;

}
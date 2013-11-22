// Shader that makes you puke by Gaeel (Sugardude), modified daxnitro curvature.

uniform float time;
varying vec3 vertex_color;

void main()
{
	vec4 position = gl_ModelViewMatrix *  gl_Vertex;

	float dist2;//distance squared
	dist2 = position.z * position.z;

	if(time < 5000.0){
		position.y += 5.0 * dist2/1000.0*time;
	}
	float y = position.y;
	float x = position.x;
	
	vertex_color = gl_Color.xyz;
	gl_Position = gl_ProjectionMatrix * position;
   
}
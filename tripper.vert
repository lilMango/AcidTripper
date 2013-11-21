uniform float time;
varying vec3 vertex_color;

void main()
{
	vec4 position = gl_ModelViewMatrix *  gl_Vertex;

	float dist2;//distance squared
	dist2 = position.x * position.x + position.z * position.z;
	position.y += 10.0 * sin(dist2 * sin(time)/1000.0);
	float y = position.y;
	float x = position.x;
	
	float om = sin(dist2 * sin(time) / 5000.0) * sin(time);
	position.y = x*sin(om) + y*cos(om);
	position.x = x*cos(om) - y*sin(om);
	
	vertex_color = gl_Color.xyz;
	gl_Position = gl_ProjectionMatrix * position;
   
}
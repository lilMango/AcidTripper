uniform float time;
varying vec3 vertex_color;

varying vec4 diffuse, ambient;
varying vec3 normal, lightDir, halfVector;
varying float dist;


void main()
{
	//per pixel lighting
	vec4 ecPos;
	vec3 aux;
	normal = normalize(gl_NormalMatrix * gl_Normal);
	ecPos = gl_ModelViewMatrix * gl_Vertex;
	aux = vec3(gl_LightSource[0].position - ecPos);
	lightDir = normalize(aux);
	dist = length(aux);
	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;



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
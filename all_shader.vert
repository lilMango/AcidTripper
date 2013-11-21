
varying vec3 normal;
varying vec4 ambientGlobal, ecPos;

varying vec3 lightDir0, halfVector0;
varying vec4 diffuse0, ambient0;
varying float dist0, NdotL0;

varying vec3 lightDir1, halfVector1;
varying vec4 diffuse1, ambient1;
varying float dist1, NdotL1;

void main()
{	
	vec4 new_Vert = gl_Vertex;
	ecPos = gl_ModelViewMatrix*gl_Vertex;
	normal = normalize(gl_NormalMatrix * gl_Normal);
	ecPos = gl_Vertex;
	normal = normalize( gl_Normal);

	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;	

//TODO should I do gl_Vertex calculations not based in EYE SPACE, is good why are colors staticky?
/***** Point light *****/	

	vec3 aux0;
	aux0 = vec3(gl_LightSource[0].position-ecPos);
	dist0 =length(aux0);
	lightDir0 = normalize(aux0);
	NdotL0=max(dot(normal,lightDir0),0.0);
	vec4 repulse = vec4(0,0,0,0);
	dist0 = max(0.0, dist0);
/*
	if(NdotL0 > 0.0) { //facing right light direction
	   vec4 spotEffect0 = dot( normalize(lightDir),   
		  
	}
*/
	repulse = vec4(lightDir0 * NdotL0,0.0);

	repulse=normalize(repulse);
	repulse=repulse/(1.0 + dist0 + dist0*dist0);
	repulse = repulse / 2.0;
	new_Vert = new_Vert-repulse;


	halfVector0 = normalize(gl_LightSource[0].halfVector.xyz);
	diffuse0 = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient0 = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

	
/****** Spot Light ********/

	vec3 aux1;
	aux1 = vec3(gl_LightSource[1].position-ecPos);
	dist1 = length(aux1);
	lightDir1 = normalize(aux1);	
	NdotL1 = max(dot(normal,lightDir1), 0.0);
	
	dist1 = max(0.0,dist1);
	float spotEffect,att1;
	vec4 attract=vec4(0,0,0,0);
	if(NdotL1> 0.0){
           spotEffect = dot(normalize(gl_LightSource[1].spotDirection), normalize(-lightDir1));
	   if( spotEffect > gl_LightSource[1].spotCosCutoff) {
	       spotEffect = pow(spotEffect, gl_LightSource[1].spotExponent);
	       att1 = spotEffect / (1.0 + 
	       	      		    dist1 +
				    dist1 *dist1);

	       attract = att1* vec4(1,1,1,1)/2.0; 

	   }
	}
	
	new_Vert = new_Vert+attract;


	halfVector1 = normalize(gl_LightSource[1].halfVector.xyz);
	diffuse1 = gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse;
	ambient1 = gl_FrontMaterial.ambient * gl_LightSource[1].ambient;
   	

	gl_Position=gl_ProjectionMatrix*gl_ModelViewMatrix*new_Vert;
	//gl_Position = ftransform();
	
}

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



	float NdotHV0;
	vec4 color0 = vec4(0,0,0,0);
	float att0;
/*
	if(NdotL0 > 0.0){
	   att0 = 1.0 / (gl_LightSource[0].constantAttenuation+
	       	     gl_LightSource[0].linearAttenuation * dist0 +
		     gl_LightSource[0].quadraticAttenuation * dist0 * dist0);
           color0 += att0 * ((diffuse0 ) * NdotL0);
	   NdotHV0 = max(dot(normal,halfVector0),0.0);
	   color0 += att0 * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow (NdotHV0,gl_FrontMaterial.shininess); 	   
	}		
	gl_FragColor += color0;	
*/	
/****** SPOT LIGHT ***/

	float  NdotHV1, spotEffect;
	vec4 color1;// = vec4(0.0, 0.0, 0.0, 1.0);
	float att1;

 	if(NdotL1> 0.0){
   	   spotEffect = dot(normalize(gl_LightSource[1].spotDirection), normalize(-lightDir1));
	   if( spotEffect > gl_LightSource[1].spotCosCutoff) {
	       spotEffect = pow(spotEffect, gl_LightSource[1].spotExponent);
	       att1 = spotEffect / (gl_LightSource[1].constantAttenuation + 
	       	      		   gl_LightSource[1].linearAttenuation* dist1 +
				   gl_LightSource[1].quadraticAttenuation * dist1 *dist1);
	       //color1 += att1 * (diffuse1 * NdotL1 + ambient1);
	       color1 += att1 * (diffuse1 * NdotL1);
	       
	       NdotHV1 = max(dot(normal,halfVector1),0.0);
	       color1+= att1 * gl_FrontMaterial.specular * gl_LightSource[1].specular * 
	       		pow(NdotHV1,gl_FrontMaterial.shininess);
 			   

	   }
	}
	gl_FragColor += color1;;
	//gl_FragColor = vec4(vertexColor,1.0);
	
}

varying vec3 vertex_color;
varying float NdotL;
 
float random( vec3 scale, float seed ){
    return fract( sin( dot( gl_FragCoord.xyz + seed, scale ) ) * 43758.5453 + seed ) ;
}

void main(){
    vec3 color = vertex_color;
    color+= vec3(1,1,1) * NdotL;
    gl_FragColor = vec4(color, 1.0);
}
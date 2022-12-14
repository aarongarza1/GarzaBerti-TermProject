#version 460
in vec3 varNorm;
in vec3 varLdir;
in vec3 varPos; 
in vec2 tc;
uniform bool hasTexture;
uniform bool hasNormalMap;
out vec4 frag_color;
void main(void)
{
	vec3 L = normalize(varLdir);
	vec 3 N;
	if(hasNormalMap)
		N = normalize(varNorm+texture(samp1, tc).xyz*2-1);
	else
		N = normalize(varNorm);
	vec3 V = normalize(-varPos);
	vec3 R = normalize(reflect(-L, N));

	float cosTheta = dot(L, N);
	float cosPhi = dot(R, V);
	vec3 amb = ((GlobalAmbient)+(texture(samp,tc)*light.ambient * material.ambient)/1).xyz;
	vec3 dif = light.diffus.xyz * material.diffus.xyz * texture(samp,tc).xyz * max(0.0, cosTheta);
	vec3 spc = light.spec.xyz * material.spec.xyz * pow(max(0.0,cosPhi), material.shininess);
	frag_color = vec4(amb+dif+spc,1);
	
}
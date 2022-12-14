#version 460
uniform sampler2D sp;
smooth in vec3 color; 
in vec2 tc;
uniform bool isCubemap;
uniform bool hasTexture;
out vec4 frag_color;
void main(void)
{
	if(hasTexture)
		frag_color = texture2D(sp,tc);
	else
		frag_color = vec4(color.rgb, 1.0);\
}
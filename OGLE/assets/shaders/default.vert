#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexUV;
layout (location = 3) in mat4 a_InstMat;
layout (location = 7) in vec2 a_SubTexPos;
layout (location = 8) in vec2 a_SubTexSize;

out vec4 v_Color;
out vec2 v_TexUV;

uniform mat4 u_WorldToProjection;

mat4 BuildTranslation(vec3 delta)
{
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(delta, 1.0));
}

void main(){
	//gl_Position = fullTrans * vec4(a_Pos,1.0);
	//mat4 instMat = a_InstMat;
	//switch(a_ID)
	//{
	//case 0:
	//gl_Position = u_WorldToProjection * BuildTranslation(vec3(-1,0,0)) * vec4(a_Pos, 1.0);
	//break;
	//case 1:
	//gl_Position = u_WorldToProjection * BuildTranslation(vec3( 0,0,0)) * vec4(a_Pos, 1.0);
	//break;
	//case 2:
	//gl_Position = u_WorldToProjection * BuildTranslation(vec3( 1,0,0)) * vec4(a_Pos, 1.0);
	//break;
	//}
	
	gl_Position = u_WorldToProjection * a_InstMat * vec4(a_Pos, 1.0);
	//v_Color = a_Color;
	v_TexUV = a_TexUV * a_SubTexSize + a_SubTexPos;
}
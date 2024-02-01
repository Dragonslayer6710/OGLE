#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexUV;
layout (location = 3) in mat4 a_InstMat;

out vec4 v_Color;
out vec2 v_TexUV;

uniform mat4 u_WorldToProjection;

void main(){
	//gl_Position = fullTrans * vec4(a_Pos,1.0);
	//mat4 instMat = a_InstMat;
	mat4 instMat = mat4(1.0f);
	gl_Position = u_WorldToProjection * instMat * vec4(a_Pos, 1.0);
	v_Color = a_Color;
	v_TexUV = a_TexUV;
}
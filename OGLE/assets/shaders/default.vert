#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexUV;
layout (location = 3) in mat4 a_InstModelMatrix;
layout (location = 7) in vec2 a_SubTexPos;
layout (location = 8) in vec2 a_SubTexSize;

out vec4 v_Color;
out vec2 v_TexUV;

uniform mat4 u_ProjViewMatrix;


void main(){
	
	gl_Position = (u_ProjViewMatrix * a_InstModelMatrix) * vec4(a_Pos, 1.0);
	//gl_Position = u_WorldToProjection * vec4(a_Pos, 1.0);
	//v_Color = a_Color;
	v_TexUV = a_TexUV * a_SubTexSize + a_SubTexPos;
}
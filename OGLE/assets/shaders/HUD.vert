#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexUV;

uniform mat4 u_ProjViewMatrix;

out vec4 v_Color;
void main(){	
	//gl_Position = u_ProjViewMatrix * vec4(a_Pos, 1.0);
	gl_Position = vec4(a_Pos, 1.0);
	v_Color = a_Color;
}
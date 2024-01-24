#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in float a_Offset;

out vec4 v_Color;

uniform mat4 u_Transformation;

void main(){
	gl_Position = u_Transformation * vec4(a_Pos.x + a_Offset, a_Pos.yz,1.0);
	v_Color = a_Color;
}
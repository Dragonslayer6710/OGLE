#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in mat4 a_InstanceTransform;

out vec4 v_Color;

uniform mat4 u_Projection;

uniform mat4 u_WorldToView;

uniform mat4 u_Translation;
uniform mat4 u_Rotation;

void main(){
	mat4 fullTrans =  u_Translation * u_Rotation ;
	//gl_Position = fullTrans * vec4(a_Pos,1.0);
	gl_Position =u_Projection * u_WorldToView *a_InstanceTransform * fullTrans * vec4(a_Pos, 1.0);
	v_Color = a_Color;
}
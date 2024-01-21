#version 330 core

in vec4 v_Color;

out vec4 FragColor;

uniform vec4 u_Color;

void main()
{
	// outputs final color
	//FragColor = color;
	FragColor = v_Color;
	//FragColor = u_Color;
}
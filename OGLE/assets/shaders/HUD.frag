#version 430 core

in vec4 v_Color;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
	FragColor = v_Color;
}
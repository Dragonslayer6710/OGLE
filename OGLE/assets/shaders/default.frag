#version 430 core

in vec4 v_Color;
in vec2 v_TexUV;
in vec2 v_SubTexOffset;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
	//FragColor = v_Color;
	FragColor = texture(tex0, v_TexUV);
	// outputs final color
	//FragColor = color;
	//FragColor = v_Color;
	//FragColor = u_Color;
	//FragColor = texture(tex0, v_TexUV);
}
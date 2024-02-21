#version 430 core

in vec4 v_Color;
in vec2 v_TexUV;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
	//FragColor = v_Color;
	FragColor = texture(tex0, v_TexUV);
	if (FragColor == vec4(0,0,0,1))
		FragColor = v_Color;
	// outputs final color
	//FragColor = color;
	//FragColor = v_Color;
	//FragColor = u_Color;
	//FragColor = texture(tex0, v_TexUV);
}
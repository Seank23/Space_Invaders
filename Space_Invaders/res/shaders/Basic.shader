#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_Projection;

void main()
{
	TexCoords = texCoords;
	gl_Position = u_Projection * u_Model * position;
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 outColor;

in vec2 TexCoords;

uniform sampler2D u_Image;

void main()
{
	//color = vec4(TexCoords, 0.0, 1.0);
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	if (gl_FragCoord.y < 150.0)
		color = vec4(0.0, 0.8, 0.2, 1.0);
	else if (gl_FragCoord.y > 550.0)
		color = vec4(0.8, 0.0, 0.2, 1.0);

	outColor = color * texture(u_Image, TexCoords);
}
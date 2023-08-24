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
layout(location = 0) out vec4 color;

in vec2 TexCoords;

uniform sampler2D u_Image;

void main()
{
	//color = vec4(TexCoords, 0.0, 1.0);
	color = texture(u_Image, TexCoords);
}
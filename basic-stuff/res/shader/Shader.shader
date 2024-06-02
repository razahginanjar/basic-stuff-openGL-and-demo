#shader vertex
#version 330 core

layout (location = 0) in vec3 location;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 vtexture;

out vec3 vColor;
out vec2 vTextCoor;
uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * vec4(location, 1.0f);
   vColor = color;
   vTextCoor = vtexture;
};


#shader fragment
#version 330 core

in vec3 vColor;
in vec2 vTextCoor;

layout (location = 0) out vec4 FragColor;

uniform vec4 u_Color;
uniform sampler2D u_TextCoor;

void main()
{
	vec4 texColor = texture(u_TextCoor, vTextCoor);
	FragColor = /* vec4(1.0f) */texColor /* u_Color */;
	//FragColor = vec4(u_Color.x * vTextCoor.x, u_Color.y * vTextCoor.y , u_Color.z, 1.0f);
};
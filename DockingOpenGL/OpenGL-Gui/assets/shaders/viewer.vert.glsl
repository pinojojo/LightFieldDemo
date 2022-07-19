#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture_coord;
layout (location = 3) in vec3 vertex_color;
out vec2 g_texrure_coord;
out vec3 g_vertex_color;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	g_texrure_coord = vec2(texture_coord.x, texture_coord.y);
	g_vertex_color=vertex_color;
}
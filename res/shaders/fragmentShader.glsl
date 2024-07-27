#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 textCoords;

uniform vec3 color;

void main()
{
	FragColor = vec4(color * ourColor,1.0f);
}
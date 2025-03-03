#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 textCoords;

uniform vec3 color;
uniform sampler2D container_texture;
uniform sampler2D face_texture;
uniform float alpha;

void main()
{		
	//FragColor = texture(texture1, textCoords) * vec4(ourColor * color, 1) ;
	//FragColor = texture(texture1, textCoords);
	FragColor = mix(texture(container_texture, textCoords), texture(face_texture, textCoords),alpha  );
}
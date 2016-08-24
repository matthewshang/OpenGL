#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D tex;

float near = 0.1;
float far = 100.0;

float linearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
	 //color = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), 0.2);


	 //float depth = linearizeDepth(gl_FragCoord.z) / far;
	 color = texture(tex, TexCoord);
}
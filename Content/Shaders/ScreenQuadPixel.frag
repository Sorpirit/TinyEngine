#version 330 core

out vec4 FragColor;

in vec3 VertexColor;
in vec2 TexCoord;

uniform float opacity;

uniform sampler2D simpleTexture;
uniform sampler2D emojiTexture;

void main()
{
    vec2 emojiTexCoord = TexCoord;
    emojiTexCoord.x *= sign(cos(opacity * 3.14));

    FragColor = mix(texture(simpleTexture, TexCoord), texture(emojiTexture, emojiTexCoord), 0.2) * vec4(VertexColor, 1.0) * opacity;

} 
#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoord;

out vec2 v_TextureCoord;

void main() 
{
    gl_Position = position;
    v_TextureCoord = textureCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoord;

uniform vec4 u_BackgroundColor;
uniform sampler2D u_Texture;

void main()
{
    vec4 textColor = texture(u_Texture, v_TextureCoord);
    color = mix(u_BackgroundColor, textColor, textColor.a);
};

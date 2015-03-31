#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 vertexUV;

uniform mat4 mViewProj;
uniform mat3 mModel;


smooth out vec4 vertColour;
out vec2 UV;

void main()
{
	vertColour = colour;
    UV = vertexUV;

    vec4 scaledPosition = mViewProj * vec4((mModel * position).xy, 0, 1);
	gl_Position = scaledPosition;
}
#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertextUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main()
{
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	fragmentColor=vertexColor;
	fragmentPosition=vertexPosition;
	fragmentUV = vec2 ( vertextUV.x, 1.0 - vertextUV.y);
}
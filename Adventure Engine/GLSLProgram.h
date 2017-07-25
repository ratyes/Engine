#pragma once
#include <string>
#include <GL/glew.h>

using namespace std;

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const string& vertextShaderFilePath,const string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const string& attributeName);

	GLuint getUniformLocation(const string& uniformName);

	void use();
	void unUse();

private:
	void compileShader(const string filePath, GLuint id);

	int m_numAttribute;
	GLuint m_programID;
	GLuint m_vertextShaderID;
	GLuint m_fragmentShaderID;


};


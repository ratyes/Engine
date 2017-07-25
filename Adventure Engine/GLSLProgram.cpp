#include "GLSLProgram.h"
#include "Error.h"

#include <vector>
#include <fstream>

using namespace std;

GLSLProgram::GLSLProgram()
{
	m_numAttribute = 0;
	m_programID = 0;
	m_vertextShaderID = 0;
	m_fragmentShaderID = 0;

}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const string & vertextShaderFilePath, const string & fragmentShaderFilePath)
{
	m_programID = glCreateProgram();

	m_vertextShaderID=glCreateShader(GL_VERTEX_SHADER);
	if (m_vertextShaderID == 0)
	{
		fatalError("vertext Shader failed to be created");
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0)
	{
		fatalError("fragment Shader failed to be created");
	}

	compileShader(vertextShaderFilePath, m_vertextShaderID);
	compileShader(fragmentShaderFilePath, m_fragmentShaderID);
}

void GLSLProgram::compileShader(const string filePath, GLuint id)
{
	ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		fatalError("Failed top open :" + filePath);
	}

	string fileContents = "";
	string line;

	while (getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}
	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		vector<char> errorlog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorlog[0]);

		glDeleteShader(id);

		printf("%s\n", &errorlog[0]);
		fatalError("shader :"+filePath+" failed to compile");
		return;
	}
}

void GLSLProgram::linkShaders()
{
	glAttachShader(m_programID, m_vertextShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	glLinkProgram(m_programID);


	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		vector<char> errorlog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorlog[0]);

		glDeleteProgram(m_programID);
		glDeleteShader(m_vertextShaderID);
		glDeleteShader(m_fragmentShaderID);

		printf("%s\n", &errorlog[0]);
		fatalError("shaders failed to link");
		return;
	}

	glDetachShader(m_programID, m_vertextShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertextShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::addAttribute(const string & attributeName)
{
	glBindAttribLocation(m_programID, m_numAttribute, attributeName.c_str());
	m_numAttribute++;
}

GLint GLSLProgram::getUniformLocation(const string & uniformName)
{
	 GLint location=glGetUniformLocation(m_programID, uniformName.c_str());
	 if (location == GL_INVALID_INDEX)
	 {
		 fatalError("Uniform :" + uniformName + " not found in shader");
	 }
	 return location;
}

void GLSLProgram::use()
{
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unUse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}



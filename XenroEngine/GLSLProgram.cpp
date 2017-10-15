#include "GLSLProgram.h"
#include "ErrorMessages.h"
#include <fstream>
#include <string>
#include <vector>
#include "IOManager.h"
namespace Xenro {
GLSLProgram::GLSLProgram()
	: m_numAttributes(0), m_programID(0), m_fragmentShaderID(0), m_vertexShaderID(0)
{
}


GLSLProgram::~GLSLProgram()
{
	if(m_programID != 0){
	glDeleteProgram(m_programID);
	}
}

void GLSLProgram::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {

	std::string VertSource;
	std::string fragSource;

	IOManager::readFileToBuffer(vertexShaderPath, VertSource);
	IOManager::readFileToBuffer(fragmentShaderPath, fragSource);

	compileShadersFromSource(VertSource.c_str(), fragSource.c_str());

}

void GLSLProgram::compileShadersFromSource(const char* vertexShader, const char* fragmentShader) {
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	m_programID = glCreateProgram();

	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (m_vertexShaderID == 0) {
		fatalError("Failed to create Vertex Shader!");
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (m_fragmentShaderID == 0) {
		fatalError("Failed to create Fragment Shader!");
	}


	compileShader(vertexShader,  "Vertex Shader", m_vertexShaderID);
	compileShader(fragmentShader, "Fragment Shader",  m_fragmentShaderID);

}

void GLSLProgram::compileShader(const char* source, const std::string& name, GLuint id) {

	glShaderSource(id, 1, &source, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxlength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxlength);

		//The maxlength includes the NULL character
		std::vector<char> errorLog(maxlength);
		glGetShaderInfoLog(id, maxlength, &maxlength, &errorLog[0]);

		//Provide the infolog in whatever manor you deem best
		//Exit with failure
		glDeleteShader(id); //Don't create memory leak

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + name + " failed to compile!");
	}

}

void GLSLProgram::linkShaders() {

	//Attach our shaders to our program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	//Link our program
	glLinkProgram(m_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(m_programID);
		//Don't leak shaders either.
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
}

//adds an attribute to the shader. Needs to be called between compiling and linking.
void GLSLProgram::addAttribute(const std::string &attributeName) {
	glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + uniformName + " not found in Shader!");
	}
	return location;
}

void GLSLProgram::use() {
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

//enable the shader, and all its attributes.
void GLSLProgram::unuse() {
	glUseProgram(0);

	//enable all the attibutes we added with addAttribute.
	for (int i = 0; i < m_numAttributes; i++) {
		glDisableVertexAttribArray(i);
		}
	}
}
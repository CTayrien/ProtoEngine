/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "shader.h"

#include <GL/glew.h>
#include <iostream>

shader::shader()
{
}

shader::shader(std::string filenamev, std::string filenamef)
	:asset(std::vector<std::string>{filenamev, filenamef})
{
}

shader::~shader()
{
}

bool shader::load()
{
	// If already loaded, copy from asset map instead of loading again
	if (nullptr != assets[key]) {
		*this = *(shader*)(assets[key]);
		return true;
	}

	// Create program & shaders in memory
	id = glCreateProgram();
	ids[0] = glCreateShader(GL_VERTEX_SHADER);
	ids[1] = glCreateShader(GL_FRAGMENT_SHADER);
	
	for (int i = 0; i < 2; i++)
	{
		// Try read
		char* shaderCode = read(filenames[i].c_str());
		if (!shaderCode) {
			printf("\nShader not found: %s\n", filenames[i].c_str());
			unload();
			return false;
		}

		// Try upload & compile
		glShaderSource(ids[i], 1, &shaderCode, 0);
		delete[] shaderCode;
		glCompileShader(ids[i]);
		GLint compiled;
		glGetShaderiv(ids[i], GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint logLength;
			glGetShaderiv(ids[i], GL_INFO_LOG_LENGTH, &logLength);
			GLchar *log = new GLchar[logLength];
			glGetShaderInfoLog(ids[i], logLength, 0, log);
			printf ("\nShader failed to compile: %s\n", log);
			delete[] log;
			unload();
			return false;
		}
	}
	
	// Try attach & link program
	glAttachShader(id, ids[0]);
	glAttachShader(id, ids[1]);
	glLinkProgram(id);
	GLint linked;
	glGetProgramiv(id, GL_LINK_STATUS, &linked);
	if (!linked) {
		GLint logLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
		GLchar *log = new GLchar[logLength];
		glGetProgramInfoLog(id, logLength, 0, log);
		printf("\nShader link failed:\n%s\n%s\n%s\n", filenames[0].c_str(), filenames[1].c_str(), log);
		unload();
		delete[] log;
		return false;
	}

	loaded = true;

	// Save a copy of this asset in the asset manager
	assets[key] = new shader(*this);

	return true;
}

void shader::use()
{	
	glUseProgram(id);
}

void shader::unload()
{	
	glDeleteProgram(id);
	glDeleteShader(ids[0]);
	glDeleteShader(ids[1]);
	
	id = ids[0] = ids[1] = 0;
}
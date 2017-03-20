/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "shader.h"
#include "fileio.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

shader::shader()
{
}


shader::shader(string filenamev, string filenamef)
{
	this->filenamev = filenamev;
	this->filenamef = filenamef;
}

shader::~shader()
{
}

bool shader::load()
{	
	// Compile shaders
	if (!compile(GL_VERTEX_SHADER)) return false;
	if (!compile(GL_FRAGMENT_SHADER)) {
		glDeleteShader(vid);
		return false;
	}
	
	// Create program, attach and link shaders
	id = glCreateProgram();
	glAttachShader(id, vid);
	glAttachShader(id, fid);
	glLinkProgram(id);
	
	// Check if it worked
	GLint linked;
	glGetProgramiv(id, GL_LINK_STATUS, &linked);
	if (linked) return true;

	// If failed, get and print info log
	GLint logLength;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
	GLchar *log = new GLchar[logLength];
	glGetProgramInfoLog(id, logLength, 0, log);
	std::cout << "\nShader link failed: \n" << log;
	delete[] log;

	// Clean up failed resources
	glDeleteProgram(id);
	glDeleteShader(vid);
	glDeleteShader(fid);
	
	return false;
}

bool shader::compile(GLenum shaderType)
{
	uint32_t& sid = (shaderType == GL_VERTEX_SHADER) ? vid : fid;
	string& filename = (shaderType == GL_VERTEX_SHADER) ? filenamev : filenamef;

	char* shaderCode = fileio::read(filename.c_str());
	
	// Compile
	sid = glCreateShader(shaderType);
	glShaderSource(sid, 1, &shaderCode, 0);
	delete[] shaderCode;
	glCompileShader(sid);
	GLint compiled;
	glGetShaderiv(sid, GL_COMPILE_STATUS, &compiled);
	if (compiled) return true;

	// If it didn't compile...
	GLint logLength;
	glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &logLength);
	GLchar *log = new GLchar[logLength];
	glGetShaderInfoLog(sid, logLength, 0, log);
	std::cout << "\nShader failed to compile: \n" << log;
	delete[] log;
	glDeleteShader(sid);

	return false;
}

bool shader::use()
{	
	glUseProgram(id);
}

void shader::unload()
{	
	glDeleteProgram(id);
	glDeleteShader(vid);
	glDeleteShader(fid);
	
	id = vid = fid = -1;
}

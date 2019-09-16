#pragma once

#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include <iostream>
#include <map>

namespace Managers {
	class Shader_Manager {
	private:
		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shaderType, std::string source, const std::string& shaderName); //create and compile a (vertex or fragment) shader
		static std::map<std::string, GLuint> programs;
	public:
		Shader_Manager(); //constructor
		~Shader_Manager(); //destructor
		void CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename); //uses ReadShader to extract shader contents to create both v and f shaders and load into program
		static const GLuint GetShader(const std::string&);
		static void DeleteShader(const std::string&);
	};
}
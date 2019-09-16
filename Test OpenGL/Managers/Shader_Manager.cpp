#include "Shader_Manager.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace Managers;

//activate the map from .h
std::map<std::string, GLuint> Shader_Manager::programs;

Shader_Manager::Shader_Manager() {}
//destructor, free mem bro
Shader_Manager::~Shader_Manager() {
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); i++) {
		GLuint prgrm = i->second;
		glDeleteProgram(prgrm);
	}
	programs.clear();
}


std::string Shader_Manager::ReadShader(const std::string& filename){
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);
	//errorcheck
	if (!file.good()) {
		std::cout << "File not read" << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

//load shader code into object handles
GLuint Shader_Manager::CreateShader(GLenum shaderType, std::string source, const std::string& shaderName) {
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType); //make empty shader object (handle)
	const char *shader_code_ptr = source.c_str(); //get pointer to source of code
	const int shader_code_size = source.size(); //get size of code

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size); //loads shader object with the code
	glCompileShader(shader); //compiles code for new shader
	//errorcheck
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//errorcheck
	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

//create a program and add the shaders to it
void Shader_Manager::CreateProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename) {
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	char vShaderName[] = "vertex shader";
	char fShaderName[] = "fragment shader";
	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, vShaderName); //call make shader with vertex
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, fShaderName); //call make shader with fragment

	int link_result = 0;

	GLuint program = glCreateProgram(); //make empty program
	glAttachShader(program, vertex_shader); //attach vshader
	glAttachShader(program, fragment_shader); //attach fshader

	glLinkProgram(program); //link the program
	//errorcheck with linking
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	//errorcheck
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
	}
	programs.insert({shaderName, program});
}

const GLuint Shader_Manager::GetShader(const std::string& fileName) {
	if (programs.count(fileName))
		return programs.at(fileName);
}

void Shader_Manager::DeleteShader(const std::string& fileName) {
	if (programs.count(fileName))
		programs.erase(fileName);
}

//THE ERRORCHECKS ARE IMPORTANT TO SAVE LOTS OF TIME WHEN DEBUGGING
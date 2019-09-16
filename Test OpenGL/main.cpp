#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeGlut\freeglut.h"
#include <iostream>
#include "Core\GameModels.h"
#include "Managers\Shader_Manager.h"

#include<stdio.h>;
#include<stdlib.h>;
#include<fstream>;
#include<vector>;

using namespace Managers;

Models::GameModels* gameModels;
Shader_Manager* shaderManager; //since using Managers namespace
GLuint program; //declare program

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear color and depth buffers
	glClearColor(0, 0.3, 0.3, 1); //set the cleared color to grey

	//why is this here, bind has no effect on drawing the triangle
	glBindVertexArray(gameModels->GetModel("triangle1"));

	glUseProgram(program); //use THIS program we made
	glDrawArrays(GL_TRIANGLES, 0, 3); //draw 3 vertices as triangles
	glutSwapBuffers(); //swap back and forward buffers
}

void closeCallback() {
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init() {
	glEnable(GL_DEPTH_TEST); //depth test

	gameModels = new Models::GameModels();
	gameModels->CreateTriangleModel("triangle1");

	//create a compiled program of shaders
	shaderManager = new Shader_Manager(); //using namespace Managers
	shaderManager->CreateProgram("colorShader", "Shaders\\Vertex_Shader.glsl", "Shaders\\Fragment_Shader.glsl");
	program = Shader_Manager::GetShader("colorShader"); //set program to use
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv); //init Glut
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //init depth, init double buffering, init colors
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Draw triangle now"); //make window
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glewInit(); //glew 4.3

	Init();

	glutDisplayFunc(renderScene); //callback to run the render function initialized above
	glutCloseFunc(closeCallback);

	glutMainLoop();

	delete gameModels;
	delete shaderManager;
	return 0;
}
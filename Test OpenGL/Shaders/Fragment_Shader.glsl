#version 430 core
//framebuffer
layout(location = 0) out vec4 out_color; //different buffer than the glenable one, thus different index

in vec4 color; //must match with out color for vshader

//out vec4 color;

void main(){
	out_color = color;
	//color = vec4(0.0, 1.0, 0.0, 1.0);
}
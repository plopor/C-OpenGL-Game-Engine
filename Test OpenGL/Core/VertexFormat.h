#ifndef  VertexFormat_H_
#define VertexFormat_H_

#include "glm\glm.hpp"

struct VertexFormat
{
	//attributes *note, the order matters, stores one type contiguously at a time in this order
	glm::vec3 position;
	glm::vec4 color;

	VertexFormat(const glm::vec3 &ipos, const glm::vec4 &iColor)
	{
		position = ipos;
		color = iColor;
	}
};

#endif
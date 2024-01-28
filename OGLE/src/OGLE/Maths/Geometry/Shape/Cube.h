#pragma once

#include "OGLE/Maths/Geometry/Shape/Shape.h"
namespace OGLE {

	static std::vector<Vertex> cubeVertices =
	{
		Vertex{glm::vec3(1.0f,-1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //0 Right
		Vertex{glm::vec3(1.0f,-1.0f,-1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //1
		Vertex{glm::vec3(1.0f, 1.0f,-1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //2
		Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //3

		Vertex{glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //4 Left
		Vertex{glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //5
		Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //6
		Vertex{glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //7

		Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //8 Top
		Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //9
		Vertex{glm::vec3(1.0f, 1.0f,-1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //10
		Vertex{glm::vec3(-1.0f, 1.0f,-1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //11

		Vertex{glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //12 Bottom
		Vertex{glm::vec3(1.0f,-1.0f,-1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //13
		Vertex{glm::vec3(1.0f,-1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //14
		Vertex{glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //15

		Vertex{glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //16 Front
		Vertex{glm::vec3(1.0f,-1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //17
		Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //18
		Vertex{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //19

		Vertex{glm::vec3(1.0f,-1.0f, -1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, //20 Back
		Vertex{glm::vec3(-1.0f,-1.0f, -1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, //21
		Vertex{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, //22
		Vertex{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, //23
	};

	static std::vector<GLushort> cubeIndices =
	{
		 0,  1,  2,
		 2,  3,  0,

		 4,  5,  6,
		 6,  7,  4,

		8,  9, 10,
		10, 11,  8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,

	};


	class Cube : public Shape
	{
	public:
		Cube()
			: Shape(cubeVertices, cubeIndices) {}
	};
}


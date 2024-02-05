#pragma once

#include "OGLE/Maths/Geometry/Drawable.h"
namespace OGLE {

	static std::vector<Vertex> s_CubeVertices = 
	
	{
		{glm::vec3(0.5f,-0.5f, 0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)}, //0 Right
		{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)}, //1
		{glm::vec3(0.5f, 0.5f,-0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)}, //2
		{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)}, //3
	
		{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)}, //4 Left
		{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)}, //5
		{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)}, //6
		{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)}, //7
	
		{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)}, //8 Top
		{glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)}, //9
		{glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)}, //10
		{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)}, //11
	
		{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)}, //12 Bottom
		{glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)}, //13
		{glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)}, //14
		{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)}, //15
	
		{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)}, //16 Front
		{glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)}, //17
		{glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)}, //18
		{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)}, //19
	
		{glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 0.5f), glm::vec2(0.0f)}, //20 Back
		{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 0.5f), glm::vec2(0.0f)}, //21
		{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec2(0.0f)}, //22
		{glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), glm::vec2(0.0f)}, //23
	};

	static std::vector<GLushort> s_CubeIndices =
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


	class Cube : public Drawable
	{
	public:
		Cube()
			: Drawable(new Mesh(s_CubeVertices, s_CubeIndices), nullptr) {}
	};
}


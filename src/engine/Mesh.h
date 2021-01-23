/*#pragma once

#include "glm/glm.hpp"
#include "renderer/OpenGL/opl.h"
#include <string>
#include <vector>
#include <memory>
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoords;
};

struct Tex
{
	unsigned int id;
	std::string Type;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Tex> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Tex> textures);
	void Draw(gl::Shader& shader);
private:
	unsigned int VAO, VBO, EBO;

	void SetupMesh();

};*/


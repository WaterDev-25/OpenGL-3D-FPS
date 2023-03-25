#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "glshader.hpp"

#define MAX_BONE_INFLUENCE 4

// Vertex struct
struct SVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	
	GLint boneIds[MAX_BONE_INFLUENCE];
	GLfloat weights[MAX_BONE_INFLUENCE];
};

// Texture struct
struct STexture
{
	GLuint id;
	
	std::string type;
	std::string path;
};

class CMesh
{
public:
	// Constructor
	CMesh(std::vector<SVertex> vertices, std::vector<GLuint> indices, std::vector<STexture> textures);

	// Destructor
	~CMesh();

	// Render the mesh
	void Draw(CGLShader* shader);

private:
	// Mesh data
	std::vector<SVertex> m_vertices;
	std::vector<GLuint> m_indices;
	std::vector<STexture> m_textures;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;

	// Initialize all the buffer objects/arrays
	void SetupMesh();
};

#endif // MESH_HPP

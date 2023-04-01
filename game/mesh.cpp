#include "mesh.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CMesh::CMesh(std::vector<SVertex> vertices, std::vector<GLuint> indices, std::vector<STexture> textures) :
	m_vertices(vertices),
	m_indices(indices),
	m_textures(textures)
{
	this->SetupMesh();
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CMesh::~CMesh()
{
	// RAII
	// --
}

// ------------------------------------------------------
// Purpose: Render the mesh
// ------------------------------------------------------
void CMesh::Draw(CGLShader* shader)
{
	// Bind appropriate textures
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint normalNr = 1;
	GLuint heightNr = 1;

	for(GLuint i = 0; i < this->m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = this->m_textures[i].type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);

		shader->SetInt(name + number, i);

		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, this->m_textures[i].id);
	}

	// Draw mesh
	glBindVertexArray(this->m_vao);
	glDrawElements(GL_TRIANGLES, (GLuint)this->m_indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

// ------------------------------------------------------
// Purpose: Initialize all the buffer objects/arrays
// ------------------------------------------------------
void CMesh::SetupMesh()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->m_vao);
	glGenBuffers(1, &this->m_vbo);
	glGenBuffers(1, &this->m_ebo);

	glBindVertexArray(this->m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(SVertex), &this->m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(GLuint), &this->m_indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, normal));
	glEnableVertexAttribArray(1);
	
	// Vertex texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, texCoords));
	glEnableVertexAttribArray(2);
	
	// Vertex tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, tangent));
	glEnableVertexAttribArray(3);
	
	// Vertex bitangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, bitangent));
	glEnableVertexAttribArray(4);
	
	// Ids
	glVertexAttribPointer(5, 4, GL_INT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, boneIds));
	glEnableVertexAttribArray(5);
	
	// Weights
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, weights));
	glEnableVertexAttribArray(6);

	glBindVertexArray(0);
}

#ifndef MODEL_HPP
#define MODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <stb/stb_image.h>

#include <vector>
#include <string>

#include "mesh.hpp"
#include "glshader.hpp"

GLuint LoadTexture(std::string path);

class CModel
{
public:
	// Constructor
	CModel(std::string const &path, GLboolean gamma = false);

	// Destructor
	~CModel();

	// Render the model
	void Draw(CGLShader* shader);

private:
	// Model data
	std::vector<STexture> m_texturesLoaded;
	std::vector<CMesh> m_meshes;
	std::string m_path;

	GLboolean m_gammaCorrection;

	// Loads a model with assimp
	void LoadModel(std::string const& path);

	// Processes a node in recursive fashion
	void ProcessNode(aiNode* node, const aiScene* scene);

	CMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	// Checks all material
	std::vector<STexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif // MODEL_HPP

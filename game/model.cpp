#include "model.hpp"

GLuint LoadTexture(std::string path)
{
	GLuint id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	GLint width;
	GLint height;
	GLint nrChannels;

	GLenum format{};

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		switch (nrChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			std::cerr << "Texture type undefined" << std::endl;
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;

		return 1;
	}

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return id;
}

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CModel::CModel(std::string const& path, GLboolean gamma) :
	m_path(path), m_gammaCorrection(gamma)
{
	this->LoadModel(path);
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CModel::~CModel()
{
	// RAII
	//
}

// ------------------------------------------------------
// Purpose: Render the model
// ------------------------------------------------------
void CModel::Draw(CGLShader* shader)
{
	for (GLuint i = 0; i < this->m_meshes.size(); i++)
		this->m_meshes[i].Draw(shader);
}

// ------------------------------------------------------
// Purpose: Loads a model with assimp
// ------------------------------------------------------
void CModel::LoadModel(std::string const& path)
{
	// Flip texture
	//stbi_set_flip_vertically_on_load(true);

	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	// Check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
		return;
	}

	// Proccess root node recursively
	this->ProcessNode(scene->mRootNode, scene);
}

// ------------------------------------------------------
// Purpose: Processes a node in recursive fashion
// ------------------------------------------------------
void CModel::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Process each mesh loacated at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->m_meshes.push_back(this->ProcessMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
		this->ProcessNode(node->mChildren[i], scene);
}

CMesh CModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	std::vector<SVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<STexture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		SVertex vertex;

		// Positions
		glm::vec3 vector = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		vertex.position = vector;

		// Normals
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;

			vertex.normal = vector;
		}

		// Texture coordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 texCoords = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
			vertex.texCoords = texCoords;

			// Tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;

			// Bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
		}
		else
			vertex.texCoords = glm::vec2(0.0f);

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		// Retieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// Diffuse maps
	std::vector<STexture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// Specular maps
	std::vector<STexture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// Normal maps
	std::vector<STexture> normalMaps = this->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// Height maps
	std::vector<STexture> heightMaps = this->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return CMesh(vertices, indices, textures);
}

// ------------------------------------------------------
// Purpose: Checks all material
// ------------------------------------------------------
std::vector<STexture> CModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<STexture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;

		mat->GetTexture(type, i, &str);

		// Check if texture was loaded before
		bool skip = false;

		for (GLuint j = 0; j < this->m_texturesLoaded.size(); j++)
		{
			if (std::strcmp(this->m_texturesLoaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(this->m_texturesLoaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			STexture texture;

			texture.id = LoadTexture(this->m_path.substr(0, this->m_path.find_last_of('/')) + '/' + std::string(str.C_Str()));
			texture.type = typeName;
			texture.path = str.C_Str();

			textures.push_back(texture);

			this->m_texturesLoaded.push_back(texture);
		}
	}

	return textures;
}

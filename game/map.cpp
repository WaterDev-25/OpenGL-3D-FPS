#include "map.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CMap::CMap(std::string path)
{
	// Load map model
	this->m_pMapModel = new CModel(path);

	// Load collisions.json
	size_t last_slash_idx = path.find_last_of("/\\");

	std::ifstream f(path.substr(0, last_slash_idx) + "\\collisions.json");
	nlohmann::json data = nlohmann::json::parse(f);

	for (auto& pos : data)
	{
		SAABB aabb;
		aabb.position = glm::vec3(pos["x"], pos["y"], pos["z"]);
		aabb.size = glm::vec3(pos["w"], pos["h"], pos["d"]);
		aabb.axis = glm::vec3(pos["lx"], pos["ly"], pos["lz"]);

		this->m_aabbs.push_back(aabb);
	}
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CMap::~CMap()
{
	// RAII
	delete this->m_pMapModel;
}

// ------------------------------------------------------
// Purpose: Render map
// ------------------------------------------------------
void CMap::Draw(CGLShader* shader)
{
	glm::mat4 model = glm::mat4(1.0f);

	// Define matrix model
	//model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Pass model to shader
	shader->SetMat4("model", model);

	// Draw map model
	this->m_pMapModel->Draw(shader);
}

// ------------------------------------------------------
// Purpose: Get aabb vector
// ------------------------------------------------------
std::vector<SAABB> CMap::GetAABBS()
{
	return this->m_aabbs;
}

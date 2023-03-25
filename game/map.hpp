#ifndef MAP_HPP
#define MAP_HPP

#include <nlohmann/json.hpp>

#include <string>
#include <fstream>

#include "glshader.hpp"
#include "model.hpp"
#include "physics.hpp"

class CMap
{
public:
	// Constructor
	CMap(std::string path);

	// Destructor
	~CMap();

	// Render map
	void Draw(CGLShader* shader);

	// Get aabb vector
	std::vector<SAABB> GetAABBS();

private:
	CModel* m_pMapModel;

	std::vector<SAABB> m_aabbs;
};

#endif // MAP_HPP

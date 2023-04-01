#include "config.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CConfig::CConfig(std::string path)
{
    // Read config file
    std::ifstream f(path);

    nlohmann::json data = nlohmann::json::parse(f);

    this->m_port = data["port"];
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CConfig::~CConfig()
{
    // RAII
    // --
}

// ------------------------------------------------------
// Purpose: Get server port
// ------------------------------------------------------
int CConfig::GetPort()
{
    return this->m_port;
}

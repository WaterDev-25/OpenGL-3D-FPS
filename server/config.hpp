#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

class CConfig
{
public:
    // Constructor
    CConfig(std::string path);

    // Destructor
    ~CConfig();

    // Getters
    // Get server port
    int GetPort();

private:
    int m_port;
};

#endif // CONFIG_HPP

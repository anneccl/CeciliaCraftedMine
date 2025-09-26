#ifndef SHADER_H__
#define SHADER_H__

#include "define.h"
#include <string>

class Shader
{
public:
    Shader();
    ~Shader();
    bool Load(const std::string &vertFile, const std::string &fragFile);
    void SetValue(rl::ShaderLocationIndex locIndex, const void *value, int uniformType);

    operator const rl::Shader &() const;

    // Empecher la copie
    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

private:
    rl::Shader m_shader;
};

#endif // SHADER_H__

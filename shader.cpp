#include "shader.h"
#include "define.h"

Shader::Shader()
{
}

Shader::~Shader()
{
    rl::UnloadShader(m_shader);
}

bool Shader::Load(const std::string &vertexShader, const std::string &fragmentShader)
{
    m_shader = rl::LoadShader(rl::TextFormat("assets/shaders/%s", vertexShader.c_str()), rl::TextFormat("assets/shaders/%s", fragmentShader.c_str()));

    m_shader.locs[rl::SHADER_LOC_VECTOR_VIEW] = rl::GetShaderLocation(m_shader, "viewPos");

    int ambientLoc = rl::GetShaderLocation(m_shader, "ambient");

    // static const float values[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    // static const float values[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    static const float values[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    rl::SetShaderValue(m_shader, ambientLoc, values, rl::SHADER_UNIFORM_VEC4);
    return true;
}

void Shader::SetValue(rl::ShaderLocationIndex locIndex, const void *value, int uniformType)
{
    rl::SetShaderValue(m_shader, m_shader.locs[locIndex], value, uniformType);
}

Shader::operator const rl::Shader &() const
{
    return m_shader;
}
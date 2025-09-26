#include "texture.h"
#include <cassert>

Texture::Texture(const std::string &filename) : m_isValid(false)
{
    if (filename != "")
        Load(filename);
}

Texture::~Texture()
{
    if (IsValid())
        rl::UnloadTexture(m_texture);
}

bool Texture::Load(const std::string &filename, bool smooth)
{
    rl::Image im = rl::LoadImage(("assets/textures/" + filename).c_str());
    rl::ImageFlipVertical(&im);
    m_texture = rl::LoadTextureFromImage(im);
    rl::UnloadImage(im);

    rl::SetTextureFilter(m_texture, smooth ? rl::TEXTURE_FILTER_BILINEAR : rl::TEXTURE_FILTER_POINT);

    m_isValid = true;
    return true;
}

bool Texture::Load(const rl::Image &image, bool smooth)
{
    m_texture = rl::LoadTextureFromImage(image);
    // TODO set as parameter here and in Load(std::string) ??
    // rl::SetTextureFilter(m_texture, rl::TEXTURE_FILTER_POINT);
    rl::SetTextureFilter(m_texture, smooth ? rl::TEXTURE_FILTER_BILINEAR : rl::TEXTURE_FILTER_POINT);
    // rl::SetTextureFilter(m_texture, rl::TEXTURE_FILTER_BILINEAR);

    // SetTextureWrap(m_texture, rl::TEXTURE_WRAP_REPEAT);
    SetTextureWrap(m_texture, rl::TEXTURE_WRAP_CLAMP);
    // SetTextureWrap(m_texture, rl::TEXTURE_WRAP_MIRROR_REPEAT);
    // SetTextureWrap(m_texture, rl::TEXTURE_WRAP_MIRROR_CLAMP);

    m_isValid = true;
    return true;
}

bool Texture::IsValid() const
{
    return m_isValid;
}

Texture::operator const rl::Texture &() const
{
    return m_texture;
}
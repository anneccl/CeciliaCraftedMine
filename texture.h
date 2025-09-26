#ifndef TEXTURE_H__
#define TEXTURE_H__

#include "define.h"
#include <string>

class Texture
{
public:
    Texture(const std::string &filename = "");
    ~Texture();

    bool Load(const std::string &filename, bool smooth = true);
    bool Load(const rl::Image &image, bool smooth = true);
    bool IsValid() const;

    operator const rl::Texture &() const;

    // Empecher la copie
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

private:
    rl::Texture2D m_texture;
    bool m_isValid;
};

#endif // TEXTURE_H__

#ifndef TEXTUREATLAS_H__
#define TEXTUREATLAS_H__

#include "define.h"
#include "texture.h"
#include <string>
#include <vector>

class TextureAtlas
{
public:
    typedef unsigned int SubTextureIndex;

    struct SubTextureInfo
    {
        SubTextureIndex index;
        std::string filename;
        float u, v, s;

        SubTextureInfo(SubTextureIndex index, const std::string &filename) : index(index), filename(filename) {}
    };

public:
    TextureAtlas();
    ~TextureAtlas();
    SubTextureIndex AddTexture(const std::string &filename);
    bool Generate(int textureSize, bool smooth = false);

    bool IsValid() const;

    const SubTextureInfo &GetSubTextureInfo(TextureAtlas::SubTextureIndex index) const;

    operator const Texture &() const;

    // Empecher la copie
    TextureAtlas(const TextureAtlas &) = delete;
    TextureAtlas &operator=(const TextureAtlas &) = delete;

private:
    bool IsPowerOfTwo(unsigned int x)
    {
        return ((x != 0) && ((x & (~x + 1)) == x));
    }

    void TextureIndexToCoord(SubTextureIndex idx, float &u, float &v, float &s) const;

private:
    std::vector<SubTextureInfo> m_subTextures;

    // On utilise un std::map pour avoir des valeurs uniques
    // typedef std::map<std::string, TextureInfo> TextureList;
    // TextureList m_textureList;

    SubTextureIndex m_currentTextureIndex = 0;
    bool m_isValid = false;
    unsigned int m_nbTexturePerSide = 0;

    Texture m_texture;
};

#endif // TEXTUREATLAS_H__

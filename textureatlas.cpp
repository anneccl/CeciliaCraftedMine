#include "textureatlas.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>

TextureAtlas::TextureAtlas()
{
}

TextureAtlas::~TextureAtlas()
{
    if(IsValid())
        rl::UnloadTexture(m_texture);
}

TextureAtlas::SubTextureIndex TextureAtlas::AddTexture(const std::string &filename)
{
    // If the texture is already in the list, return it's id
    auto it = std::find_if(m_subTextures.begin(), m_subTextures.end(), [filename](const auto &tex)
                           { return tex.filename == filename; });

    if(it != m_subTextures.end())
        return it->index;

    m_subTextures.push_back(SubTextureInfo(m_subTextures.size(), filename));
    return m_subTextures.size() - 1;
}

bool TextureAtlas::Generate(int textureSize, bool smooth)
{
    // Arrondir sur la puissance de 2 superieure
    m_nbTexturePerSide = (int)sqrt((float)m_subTextures.size());
    if(m_nbTexturePerSide * m_nbTexturePerSide < m_subTextures.size())
        m_nbTexturePerSide++;
    while(!IsPowerOfTwo(m_nbTexturePerSide))
        m_nbTexturePerSide++;

    int atlasSize = textureSize * m_nbTexturePerSide;
    // rl::Image atlas = rl::GenImageColor(atlasSize, atlasSize, rl::MAGENTA);
    rl::Image atlas = rl::GenImageColor(atlasSize, atlasSize, rl::BLANK);

    for(size_t i = 0; i < m_nbTexturePerSide * m_nbTexturePerSide; ++i)
    {
        int imgIdx = i;
        int x = imgIdx % m_nbTexturePerSide;
        int y = m_nbTexturePerSide - 1 - imgIdx / m_nbTexturePerSide;

        if(i < m_subTextures.size())
        {
            auto &subTex = m_subTextures[i];

            std::cout << "Loading '" << subTex.filename << "'..." << std::endl;

            rl::Image im = rl::LoadImage(("assets/textures/" + subTex.filename).c_str());
            rl::ImageFlipVertical(&im);
            rl::ImageResize(&im, textureSize, textureSize);

            // Clear color by drawing transparent color
            rl::ImageDrawRectangle(&atlas, x * textureSize, y * textureSize, textureSize, textureSize, {0, 0, 0, 0});

            rl::ImageDraw(&atlas, im, {0, 0, (float)textureSize, (float)textureSize}, {(float)x * (float)textureSize, (float)y * (float)textureSize, (float)textureSize, (float)textureSize}, rl::WHITE);

            rl::UnloadImage(im);

            TextureIndexToCoord(subTex.index, subTex.u, subTex.v, subTex.s);
        }
        else
        {
            // Use magenta color for unused texture slots
            rl::ImageDrawRectangle(&atlas, x * textureSize, y * textureSize, textureSize, textureSize, rl::MAGENTA);
        }
    }

    m_texture.Load(atlas, smooth);

    m_isValid = true;
    return true;
}

bool TextureAtlas::IsValid() const
{
    return m_isValid;
}

const TextureAtlas::SubTextureInfo &TextureAtlas::GetSubTextureInfo(TextureAtlas::SubTextureIndex index) const
{
    assert(index < m_subTextures.size());

    return m_subTextures[index];
}

void TextureAtlas::TextureIndexToCoord(SubTextureIndex idx, float &u, float &v, float &s) const
{
    assert(m_nbTexturePerSide != 0);

    s = 1.f / (float)m_nbTexturePerSide;

    u = (float)((unsigned int)idx % m_nbTexturePerSide) * s;
    v = (float)(m_nbTexturePerSide - 1 - (unsigned int)idx / m_nbTexturePerSide) * s;
}

TextureAtlas::operator const Texture &() const
{
    assert(IsValid());
    return m_texture;
}
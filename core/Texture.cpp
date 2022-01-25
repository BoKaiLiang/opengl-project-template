#include "Texture.h"

#include <iostream>

#include "DebugLog.h"

Texture::Texture(const std::string& imgPath)
{
    glGenTextures(1, &m_ID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(imgPath.c_str(), &m_Width, &m_Height, &nrComponents, 0);
    if (data)
    {
        switch (nrComponents)
        {
        case 1:
            m_SrcFmt = GL_R8;
            m_TexFmt = GL_RED;
            break;
        case 2:
            m_SrcFmt = GL_RG8;
            m_TexFmt = GL_RG;
            break;
        case 3:
            m_SrcFmt = GL_RGB8;
            m_TexFmt = GL_RGB;
            break;
        case 4:
            m_SrcFmt = GL_RGBA8;
            m_TexFmt = GL_RGBA;
            break;
        default:
            break;
        }

        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_SrcFmt, m_Width, m_Height, 0, m_TexFmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        DEBUG_ERROR("Texture failed to load at path : %s\n", imgPath);
        stbi_image_free(data);
    }
}

Texture* Texture::Create(const std::string& imgPath)
{
    return new Texture(imgPath);
}

Texture Texture::LoadTexture(const std::string& imgPath)
{
    return Texture(imgPath);
}

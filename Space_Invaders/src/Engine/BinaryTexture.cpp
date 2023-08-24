#include "pch.h"
#include "BinaryTexture.h"

#include <glad/glad.h>

namespace SpaceInvaders
{
    BinaryTexture::BinaryTexture(const uint8_t* pixels, const int* layout, const uint32_t color)
    {
        m_Layout = layout;
        for (int i = 0; i < m_Layout[0] * m_Layout[1]; i++)
        {
            m_Bitmap.push_back(pixels[i] * color);
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Layout[0], m_Layout[1], 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, m_Bitmap.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    BinaryTexture::~BinaryTexture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void BinaryTexture::Bind(unsigned int slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void BinaryTexture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

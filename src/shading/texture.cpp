#include <iostream>

#include "texture.h"


Texture2D::Texture2D()
    : m_width(0), 
      m_height(0), 
      m_internal_format(GL_RGB),
      m_image_format(GL_RGB), 
      m_wrap_s(GL_CLAMP_TO_EDGE), 
      m_wrap_t(GL_CLAMP_TO_EDGE), 
      m_filter_min(GL_NEAREST), 
      m_filter_max(GL_NEAREST)
{
    glGenTextures(1, &this->m_texture_ID);
}

Texture2D::~Texture2D(){}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->m_width = width;
    this->m_height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->m_texture_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->m_internal_format, width, height, 0, this->m_image_format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_filter_max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->m_texture_ID);
}
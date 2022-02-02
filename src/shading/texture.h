#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/glad.h>

/** 
 *  @file   texture.h 
 *  @brief  TODO: Fill
 *  @date   2022-30-01  
 **************************************************/

/**
 * @brief TODO: Fill
 */

class Texture2D
{
public:

    /*Constructors--------------------------------*/

    /**
     * @brief 
     * 
     */
    Texture2D();

    /**
     * @brief Texture destructor
     */
    ~Texture2D();

    /**
     * @brief TODO: Fill
     * 
     * @param param_width ...
     * @param param_height ...
     * @param param_data ...
     */
    void Generate(
        unsigned int param_width, 
        unsigned int param_height, 
        unsigned char* param_data);

    /**
     * @brief TODO: Fill
     */
    void Bind() const;

    /*Public member variables---------------------*/
    
    unsigned int m_texture_ID;

    unsigned int m_width;
    unsigned int m_height;

    unsigned int m_internal_format;
    unsigned int m_image_format;

    unsigned int m_wrap_s;
    unsigned int m_wrap_t;
    unsigned int m_filter_min;
    unsigned int m_filter_max;
};

#endif // _TEXTURE_H_
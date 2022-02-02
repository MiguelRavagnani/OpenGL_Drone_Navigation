#ifndef _SPRITE_RENDERER_
#define _SPRITE_RENDERER_

/** 
 *  @file   sprite_renderer.h 
 *  @brief  TODO: Fill
 *  @date   2022-31-01
 **************************************************/

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

/**
 * @brief Class description
 */
class SpriteRenderer
{
public:
    /*Constructors--------------------------------*/

    /**
     * @brief TODO: Fill
     * 
     * @param param_shader ...
     */
    SpriteRenderer(const Shader &param_shader);

    /**
     * @brief Destroy the Sprite Renderer object
     * 
     */
    ~SpriteRenderer();

    /**
     * @brief TODO: fill
     * 
     * @param param_texture ...
     * @param param_position ... 
     * @param param_size ...
     * @param param_rotate ...
     * @param param_color ...
     */
    void DrawSprite(
        const Texture2D &param_texture, 
        glm::vec2 param_position, 
        glm::vec2 param_size = glm::vec2(10.0f, 10.0f), 
        GLfloat param_rotate = 0.0f, 
        glm::vec3 param_color = glm::vec3(1.0f));


protected:
    /*--------------------------------------------*/
    
    /**
     * @brief TODO: fill
     * 
     */
    void initRenderData();
    
    Shader m_shader; 
    unsigned int m_quad_VAO;
};

#endif //_SPRITE_RENDERER_
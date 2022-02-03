#ifndef _SPIRE_SHEET_RENDERER_
#define _SPIRE_SHEET_RENDERER_

/** 
 *  @file   sprite_sheetR_renderer.h 
 *  @brief  Class description
 *  @author Miguel Ravagnani de Carvalho 
 *  @date   YYYY-DD-MM 
 **************************************************/
#include <iostream>

#include "sprite_renderer.h"

/**
 * @brief Class description
 */
class SpriteSheetRenderer : public SpriteRenderer
{
public:
    /*Constructors--------------------------------*/
    /**
     * @brief TODO: Fill
     * 
     * @param param_shader ...
     */
    SpriteSheetRenderer(const Shader &param_shader);

    /**
     * @brief Destroy the Sprite Renderer object
     * 
     */
    ~SpriteSheetRenderer();

    /*Methods-------------------------------------*/

    /**
     * @brief TODO: fill
     * 
     * @param param_texture ...
     * @param param_position ... 
     * @param param_frame_index ...
     * @param param_tick ...
     * @param param_sheet_size ...
     * @param param_sprite_size ...
     * @param param_rotate ...
     * @param param_color ...
     */
    void DrawSheet(
        const Texture2D &param_texture, 
        glm::vec2 param_position,
        bool param_tick,
        GLfloat param_frame_index,
        glm::vec2 param_sheet_size = glm::vec2(10.0f, 10.0f), 
        glm::vec2 param_sprite_size = glm::vec2(10.0f, 10.0f),
        GLfloat param_rotate = 0.0f, 
        glm::vec3 param_color = glm::vec3(1.0f));

private:
    /*--------------------------------------------*/
    /**
     * @brief TODO: fill
     * 
     */
    void initRenderData();

    /**
     * @brief TODO: Fill
     * 
     * @param param_frame ...
     */
    void UpdateRenderData(GLuint param_frame);
};

#endif //_SPIRE_SHEET_RENDERER_
 
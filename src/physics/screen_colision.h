#ifndef _SCREEN_COLISION_
#define _SCREEN_COLISION_

/** 
 *  @file   screen_colision.h 
 *  @brief  Class description
 *  @date   2022-06-02 
 **************************************************/

#include <glad/glad.h>
#include <glm/glm.hpp>

/**
 * @brief Class description
 */
class ScreenColision
{
public:
    /*Constructors--------------------------------*/

    /**
     * @brief Construct a new Screen Colision object
     * 
     * @param param_screen_widht ...
     * @param param_screen_height ...
     * @param param_sprite_size ...
     */
    ScreenColision(
        GLuint param_screen_widht, 
        GLuint param_screen_height,
        GLfloat param_sprite_size);

    /**
     * @brief Construct a new Screen Colision object
     * 
     * @param param_screen_widht ...
     * @param param_screen_height ...
     * @param param_screen_hitbox ...
     * @param param_sprite_size ...
     */
    ScreenColision(
        GLuint param_screen_widht, 
        GLuint param_screen_height, 
        GLfloat param_screen_hitbox,
        GLfloat param_sprite_size);

    /**
     * @brief ScreenColision desctructor
     */
    ~ScreenColision();

    /*Methods-------------------------------------*/

    /**
     * @brief TODO: Fill
     * 
     * @param param_object_position ...
     * @return true ...
     * @return false ...
     */
    bool DetectColisionY(glm::vec2 param_object_position);

    /**
     * @brief Set the Screen Hitbox object
     * 
     * @param param_screen_hitbox  ...
     */
    void SetScreenHitbox(GLfloat param_screen_hitbox);

    /**
     * @brief Get the Screen Hitbox object
     * 
     * @return GLfloat ...
     */
    GLfloat GetScreenHitbox();


private:
    /*--------------------------------------------*/

    GLuint m_screen_widht;
    GLuint m_screen_height;
    GLfloat m_screen_hitbox;
    GLfloat m_sprite_size;
};

#endif //_SCREEN_COLISION_
 
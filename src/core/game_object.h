#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

/** 
 *  @file   game_object.h 
 *  @brief  Class description
 *  @date   2022-31-01 
 **************************************************/

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sprite_renderer.h"

/**
 * @brief Class description
 */
class GameObject
{
public:
    /*Constructors--------------------------------*/
    /**
     * @brief GameObject constructor
     */
    GameObject();

    /**
     * @brief Construct a new Game Object object
     * 
     * @param param_initial_position ...
     * @param param_size ...
     * @param param_sprite ...
     * @param param_color ...
     * @param param_initial_velocity ...
     */
    GameObject(
        glm::vec2 param_initial_position, 
        glm::vec2 param_size, 
        Texture2D param_sprite, 
        glm::vec3 param_color = glm::vec3(1.0f), 
        glm::vec2 param_initial_velocity = glm::vec2(0.0f, 0.0f));
    
    /**
     * @brief GameObject desctructor
     */
    ~GameObject();

    /*Methods-------------------------------------*/
    /*Member methods*/
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_renderer 
     */
    virtual void Draw(SpriteRenderer &param_renderer);

    /*Setters-------------------------------------*/

    /**
     * @brief TODO: Fill
     * 
     * @param param_position ...
     */
    void SetPosition(glm::vec2 param_position);

    /**
     * @brief TODO: Fill
     * 
     * @param param_size ...
     */
    void SetSize(glm::vec2 param_size);

    /**
     * @brief TODO: Fill
     * 
     * @param param_velocity ...
     */
    void SetVelocity(glm::vec2 param_velocity);

    /**
     * @brief TODO: Fill
     * 
     * @param param_color ...
     */
    void GetColor(glm::vec3 param_color);

    /**
     * @brief TODO: Fill
     * 
     * @param param_rotation ...
     */
    void GetRotation(GLfloat param_rotation);

    /**
     * @brief TODO: Fill
     * 
     * @param param_is_solid ...
     */
    void GetIsSolid(bool param_is_solid);

    /**
     * @brief TODO: Fill
     * 
     * @param param_sprite ...
     */
    void GetSprite(Texture2D param_sprite);

    /*Getters-------------------------------------*/

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    glm::vec2 GetPosition();

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    glm::vec2 GetSize();

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    glm::vec2 GetVelocity();

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    glm::vec3 GetColor();

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    GLfloat GetRotation();

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    bool GetIsSolid();

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    Texture2D GetSprite();

private:
    /*--------------------------------------------*/
    
    glm::vec2 m_position;
    glm::vec2 m_size;
    glm::vec2 m_velocity;

    glm::vec3 m_color;
    GLfloat m_rotation;

    bool m_is_solid;

    Texture2D m_sprite;	
};

#endif //_GAME_OBJECT_
 
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

#include <iostream>

#include "model.h"
#include "sprite_sheet_renderer.h"

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
     * @param param_sheet_size ...
     * @param param_sprite ...
     * @param param_color ...
     * @param param_initial_velocity ...
     */
    GameObject(
        glm::vec2 param_initial_position, 
        glm::vec2 param_sheet_size, 
        Texture2D param_sprite, 
        glm::vec3 param_color = glm::vec3(1.0f), 
        glm::vec2 param_initial_velocity = glm::vec2(0.0f, 0.0f));
    
    /**
     * @brief Construct a new Game Object object
     * 
     * @param param_initial_position ...
     * @param param_sheet_size ...
     * @param param_sprite_size ...
     * @param param_sprite ...
     * @param param_color ...
     * @param param_initial_velocity ...
     */
    GameObject(
        glm::vec2 param_initial_position, 
        glm::vec2 param_sheet_size, 
        glm::vec2 param_sprite_size,
        Texture2D param_sprite, 
        glm::vec3 param_color, 
        glm::vec2 param_initial_velocity);
    
    /**
     * @brief GameObject desctructor
     */
    ~GameObject();

    /*Methods-------------------------------------*/
    /*Member methods*/
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_renderer ...
     */
    virtual void Draw(SpriteRenderer &param_renderer);

    /**
     * @brief TODO: Fill
     * 
     * @param param_renderer ...
     * @param param_tick ...
     */
    virtual void Draw(
        SpriteSheetRenderer &param_renderer,
        bool param_tick);

    /**
     * @brief ...
     * 
     * @param param_input ...
     * @return true ...
     * @return false ...
     */
    bool BoudingBox(glm::vec2 param_input);

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
     * @param param_sheet_size ...
     */
    void SetSize(glm::vec2 param_sheet_size);

    /**
     * @brief TODO: Fill
     * 
     * @param param_sprite_size ...
     */
    void SetSpriteSize(glm::vec2 param_sprite_size);

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
    void SetColor(glm::vec3 param_color);

    /**
     * @brief TODO: Fill
     * 
     * @param param_rotation ...
     */
    void SetRotation(GLfloat param_rotation);

    /**
     * @brief TODO: Fill
     * 
     * @param param_is_solid ...
     */
    void SetIsSolid(bool param_is_solid);

    /**
     * @brief TODO: Fill
     * 
     * @param param_sprite ...
     */
    void SetSprite(Texture2D param_sprite);

    /**
     * @brief TODO: Fill
     * 
     * @param param_max_rotation ...
     */
    void SetMaxRotation(GLfloat param_max_rotation);

    /**
     * @brief Set the Drone Model object
     * 
     * @param param_drone_model ...
     */
    void SetDroneModel(Model* param_drone_model);

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
    glm::vec2 GetSpriteSize();

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

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    GLfloat GetMaxRotation();

    Model* m_drone_model;
    
private:
    /*--------------------------------------------*/
    
    glm::vec2 m_position;
    glm::vec2 m_sheet_size;
    glm::vec2 m_sprite_size;
    glm::vec2 m_velocity;

    glm::vec3 m_color;

    GLfloat m_rotation;
    GLfloat m_max_rotation;

    bool m_is_solid;

    Texture2D m_sprite;

    GLfloat m_frame;

    glm::vec4 m_bouding_box;
};

#endif //_GAME_OBJECT_
 
#ifndef _GAME_
#define _GAME_

/** 
 *  @file   game.h 
 *  @brief  TODO: Fill
 *  @date   2022-30-01 
 **************************************************/
#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "sprite_sheet_renderer.h"
#include "resource_manager.h"

#include "game_object.h"
#include "screen_colision.h"
#include "physics_handler.h"

#include <GLFW/glfw3.h>

#define DEG_TO_RAD GLfloat(M_PI / 180)
#define RAD_TO_DEG GLfloat(180 / M_PI)

/**
 * @brief TODO: Fill
 */
class Game
{
public:
    /*Constructors--------------------------------*/
    /**
     * @brief Game constructor
     */
    Game();

    /**
     * @brief Game constructor
     * 
     * @param param_width ...
     * @param param_height ...
     */
    Game(
        unsigned int param_width, 
        unsigned int param_height);
    /*Constructors--------------------------------*/
    /**
     * @brief Game constructor
     */
    ~Game();

    /*Methods-------------------------------------*/
    /*Member methods*/

    /**
     * @brief Game init
     */
    void Init();

    /**
     * @brief TODO: Fill
     * 
     * @param param_delta_time ...
     */
    void ProcessInput(GLfloat param_delta_time);

    /**
     * @brief TODO: Fill
     * 
     * @param param_tick ...
     */
    void Update(bool param_tick);

    /**
     * @brief TODO: Fill
     * 
     * @param param_delta_time ...
     */
    void Render();

    /**
     * @brief TODO: Fill
     * 
     * @return ...
     */
    bool GetKeys(bool param_key);

    /**
     * @brief Set the Mouse Click 
     * 
     * @param param_mouse_click ...
     */
    void SetMouseClick(glm::vec2 param_mouse_click);

    /**
     * @brief Get the Mouse Click 
     * 
     * @return glm::vec2 ...
     */
    glm::vec2 GetMouseClick();

    /*--------------------------------------------*/
    bool m_keys[1024];

private:
    /*--------------------------------------------*/

    /**
     * @brief TODO: Fill
     */
    enum EnGameState {
        GAME_ACTIVE,          // TODO: Fill
        GAME_MENU,            // TODO: Fill
        GAME_WIN              // TODO: Fill
    }; 

    /**
     * @brief TODO: Fill
     */
    enum EnGameLoop {
        GAME_MENU,            // TODO: Fill
        GAME_LOOP_AUTOMATIC,  // TODO: Fill
        GAME_LOOP_MANUEAL     // TODO: Fill
    }; 

    /*--------------------------------------------*/
    EnGameState m_state;
    EnGameLoop m_loop;	

    unsigned int m_width;
    unsigned int m_height;

    bool m_tick;

    glm::vec2 m_mouse_click_position;

    /*--------------------------------------------*/
    /* Please, remember to delete it in destructor*/
    GameObject* m_player;
    GameObject* m_waypoint;
    SpriteRenderer  *m_renderer;
    SpriteSheetRenderer *m_sheet_renderer;
    ScreenColision *m_screen_colision;
    Model* m_drone_model;

    bool m_floor_colision;

};

#endif //_GAME_
 
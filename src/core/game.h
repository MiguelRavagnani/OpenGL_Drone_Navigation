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

    /*--------------------------------------------*/
    bool m_keys[1024];

private:
    /*--------------------------------------------*/

    /**
     * @brief TODO: Fill
     */
    enum EnGameState {
        GAME_ACTIVE,        // TODO: Fill
        GAME_MENU,          // TODO: Fill
        GAME_WIN            // TODO: Fill
    }; 

    /*--------------------------------------------*/
    EnGameState m_state;	

    unsigned int m_width;
    unsigned int m_height;

    bool m_tick;

    /*--------------------------------------------*/
    /* Please, remember to delete it in destructor*/
    GameObject* m_player;
    SpriteRenderer  *m_renderer;
    SpriteSheetRenderer *m_sheet_renderer;

};

#endif //_GAME_
 
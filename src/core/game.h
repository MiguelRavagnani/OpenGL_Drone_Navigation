#ifndef _GAME_
#define _GAME_

/** 
 *  @file   game.h 
 *  @brief  TODO: Fill
 *  @date   2022-30-01 
 **************************************************/
#include <iostream>

#include <glm/glm.hpp>

#include "sprite_renderer.h"
#include "resource_manager.h"

#include "game_object.h"

#include <GLFW/glfw3.h>
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
     */
    void ProcessInput(GLfloat param_input);

    /**
     * @brief TODO: Fill
     * 
     * @param param_input ...
     */
    void Update(GLfloat param_input);

    /**
     * @brief TODO: Fill
     * 
     * @param param_input ...
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

    /*--------------------------------------------*/
    /* Please, remember to delete it in destructor*/
    GameObject* m_player;
    SpriteRenderer  *m_renderer;

};

#endif //_GAME_
 
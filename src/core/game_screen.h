#ifndef _GAME_SCREEN_
#define _GAME_SCREEN_

/** 
 *  @file   game_screen.h 
 *  @brief  TODO: Fill
 *  @date   2022-01-02 
 **************************************************/

#include "sprite_renderer.h"

/**
 * @brief TODO: Fill
 */
class GameScreen
{
public:
    enum EnGameScreen {
        SCREEN_MENU,            // TODO: Fill
        SCREEN_CONFIG,          // TODO: Fill
        SCREEN_PLAY             // TODO: Fill
    }; 

    /*Constructors--------------------------------*/
    /**
     * @brief GameScreen constructor
     */
    GameScreen();

    /**
     * @brief GameScreen desctructor
     */
    ~GameScreen();

    /*Methods-------------------------------------*/
    /*Member methods*/

    /**
     * @brief TODO: Fill
     * 
     * @param param_screen_screen ...
     * @param param_screen_width ...
     * @param param_screen_height ...
     */
    void Load(
        EnGameScreen param_screen_screen, 
        unsigned int param_screen_width, 
        unsigned int param_screen_height);
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_renderer ...
     */
    void Draw(SpriteRenderer &param_renderer);
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_input ...
     * @return uint16_t 
     */
    uint16_t ChangeScreen(GLfloat param_input);
private:

    /**
     * @brief TODO: Fill
     * 
     * @param param_screen_width ...
     * @param param_screen_height... 
     */
    void InitGame(
        unsigned int param_screen_width, 
        unsigned int param_screen_height);

private:
    /*--------------------------------------------*/

};

#endif //_GAME_SCREEN_
 
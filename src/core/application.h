#ifndef _APPLICATION_
#define _APPLICATION_

/** 
 *  @file   application.h 
 *  @brief  Class description
 *  @author Miguel Ravagnani de Carvalho 
 *  @date   YYYY-DD-MM 
 **************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"
#include "input.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <functional>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <cmath>

std::function<void()> registered_loop;

void loop_iteration( {
    registered_loop();
})

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGH = 600;

/**
 * @brief Class description
 */
class Application
{
public:
    /*Constructors--------------------------------*/
    /**
     * @brief Application constructor
     */
    Application(
        unsigned int param_screen_width = 800U,
        unsigned int param_screen_height = 600U);

    /**
     * @brief Application desctructor
     */
    ~Application();

    /*Methods-------------------------------------*/
    /*Member methods*/

    void Run();
    void Exit();

protected:
    virtual void loop();

private:
    /*--------------------------------------------*/
    /*Member variables starting with m_*/

    unsigned int m_screen_width;
    unsigned int m_screen_height;

    Game *m_drone;
};

#endif //_APPLICATION_
 
#include "game_screen.h"

GameScreen::GameScreen() {}

GameScreen::~GameScreen() {}

void GameScreen::Load(
    EnGameScreen param_screen_screen, 
    unsigned int param_screen_width, 
    unsigned int param_screen_height)
{
    switch (param_screen_screen)
    {
    case SCREEN_MENU:
        break;
    
    case SCREEN_CONFIG:
        break;

    case SCREEN_PLAY:
        this->InitGame(param_screen_width, param_screen_height);
        break;

    default:
        break;
    }
}

void GameScreen::InitGame(
    unsigned int param_screen_width, 
    unsigned int param_screen_height) 
{
    /* Game setup code */
}
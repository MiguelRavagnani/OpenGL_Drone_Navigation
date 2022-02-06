#include "screen_colision.h"

#include <iostream>

ScreenColision::ScreenColision(
    GLuint param_screen_widht, 
    GLuint param_screen_height,
    GLfloat param_sprite_size) 
    
    : m_screen_widht (param_screen_widht),
      m_screen_height (param_screen_height),
      m_screen_hitbox (0.1f),
      m_sprite_size (param_sprite_size) {}
    
ScreenColision::ScreenColision(
    GLuint param_screen_widht, 
    GLuint param_screen_height, 
    GLfloat param_screen_hitbox,
    GLfloat param_sprite_size) 
    
    : m_screen_widht (param_screen_widht),
      m_screen_height (param_screen_height),
      m_screen_hitbox (param_screen_hitbox),
      m_sprite_size (param_sprite_size) {}
    
ScreenColision::~ScreenColision() {}

bool ScreenColision::DetectColisionY(glm::vec2 param_object_position)
{
    GLfloat hitbox_detection;

    hitbox_detection = GLfloat(m_screen_height) - (GLfloat(m_screen_height) * m_screen_hitbox);

    // std::cout << "Object Y position: " << param_object_position.y + m_sprite_size << std::endl;
    // std::cout << "Screen hitbox: " << hitbox_detection << std::endl;
    // std::cout << "Object Y position: " << (param_object_position.y + m_sprite_size >= hitbox_detection) << std::endl;

    if (param_object_position.y  + m_sprite_size >= hitbox_detection)
    {
        return true;
    }

    return false;
}

void ScreenColision::SetScreenHitbox(GLfloat param_screen_hitbox)
{
    m_screen_hitbox = param_screen_hitbox;
}

GLfloat ScreenColision::GetScreenHitbox() { return m_screen_hitbox; }
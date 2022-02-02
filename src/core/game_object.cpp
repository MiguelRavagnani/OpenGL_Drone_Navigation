#include "game_object.h"

GameObject::GameObject()

    : m_position (0.0f, 0.0f), 
      m_size (1.0f, 1.0f), 
      m_velocity (0.0f), 
      m_color (1.0f), 
      m_rotation (0.0f), 
      m_sprite (), 
      m_is_solid (false) {}


GameObject::GameObject(
    glm::vec2 param_initial_position, 
    glm::vec2 param_size, 
    Texture2D param_sprite, 
    glm::vec3 param_color, 
    glm::vec2 param_initial_velocity)

    : m_position (param_initial_position), 
      m_size (param_size), 
      m_velocity (param_initial_velocity), 
      m_color (param_color), 
      m_rotation (0.0f), 
      m_sprite (param_sprite), 
      m_is_solid (false) {}


GameObject::~GameObject() {}


void GameObject::Draw(SpriteRenderer &param_renderer)
{
    param_renderer.DrawSprite(
        this->m_sprite, 
        this->m_position, 
        this->m_size, 
        this->m_rotation, 
        this->m_color);
}


void GameObject::SetPosition(glm::vec2 param_position)
{
    m_position = param_position;
}


void GameObject::SetSize(glm::vec2 param_size)
{
    m_size = param_size;
}


void GameObject::SetVelocity(glm::vec2 param_velocity)
{
    m_velocity = param_velocity;
}


void GameObject::SetColor(glm::vec3 param_color)
{
    m_color = param_color;
}


void GameObject::SetRotation(GLfloat param_rotation)
{
    m_rotation = param_rotation;
}


void GameObject::SetIsSolid(bool param_is_solid)
{
    m_is_solid = param_is_solid;
}


void GameObject::SetSprite(Texture2D param_sprite)
{
    m_sprite = param_sprite;
}

void GameObject::SetMaxRotation(GLfloat param_max_rotation)
{
    m_max_rotation = param_max_rotation;
}


glm::vec2 GameObject::GetPosition()
{
    return m_position;
}


glm::vec2 GameObject::GetSize()
{
    return m_size;
}


glm::vec2 GameObject::GetVelocity()
{
    return m_velocity;
}


glm::vec3 GameObject::GetColor()
{
    return m_color;
}


GLfloat GameObject::GetRotation()
{
    return m_rotation;
}


bool GameObject::GetIsSolid()
{
    return m_is_solid;
}


Texture2D GameObject::GetSprite()
{
    return m_sprite;
}


GLfloat GameObject::GetMaxRotation()
{
    return m_max_rotation;
}
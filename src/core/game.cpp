#include "game.h"

/*Constructors--------------------------------*/
Game::Game()
    
    : m_width (800),
      m_height (600) {}

Game::Game(
    unsigned int param_width, 
    unsigned int param_height)
    
    : m_width (param_width),
      m_height (param_height) {}

Game::~Game()
{
    delete m_player;
	delete m_renderer;
}

void Game::Init()
{
    ResourceManager::LoadShader(
		"../src/shaders/sprite.vs", 
		"../src/shaders/sprite.frag", 
		nullptr, 
		"sprite");
	
    glm::mat4 projection = glm::ortho(
		0.0f, 
		static_cast<GLfloat>(this->m_width), 
        static_cast<GLfloat>(this->m_height), 
		0.0f, 
		-1.0f, 
		1.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	
    m_renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("../textures/gaviota.png", true, "player");
	ResourceManager::LoadTexture("../textures/bg.png", false, "background");

	glm::vec2 player_size(60.0f * 2.0f, 60.0f * 2.0f);

	glm::vec2 player_initial_velocity(500.0f, 500.0f);

	glm::vec3 player_color(1.0f);

	glm::vec2 player_inital_position = glm::vec2(
        m_width / 2.0f - player_size.x / 2.0f, 
        m_height - player_size.y);

	m_player = new GameObject(
		player_inital_position, 
		player_size, 
		ResourceManager::GetTexture("player"),
		player_color,
		player_initial_velocity);

	m_state = GAME_ACTIVE;
}

void Game::Update(GLfloat param_input)
{
    
}

void Game::ProcessInput(GLfloat param_input)
{
    if (this->m_state == GAME_ACTIVE)
    {
        GLfloat velocity = m_player->GetVelocity().x * param_input; 
		glm::vec2 new_position;

        if (this->m_keys[GLFW_KEY_A])
        {
            if (m_player->GetPosition().x >= 0.0f)
                
				new_position = glm::vec2(
					m_player->GetPosition().x - velocity, 
					m_player->GetPosition().y);

				m_player->SetPosition(new_position);
        }

        if (this->m_keys[GLFW_KEY_D])
        {
            if (m_player->GetPosition().x <= this->m_width - m_player->GetSize().x)

				new_position = glm::vec2(
					m_player->GetPosition().x + velocity, 
					m_player->GetPosition().y);

				m_player->SetPosition(new_position);
        }

		if (this->m_keys[GLFW_KEY_W])
        {
            if (m_player->GetPosition().y >= 0.0f)
                
				new_position = glm::vec2(
					m_player->GetPosition().x, 
					m_player->GetPosition().y - velocity);

				m_player->SetPosition(new_position);
        }

        if (this->m_keys[GLFW_KEY_S])
        {
            if (m_player->GetPosition().y <= this->m_width - m_player->GetSize().y)
			
				new_position = glm::vec2(
					m_player->GetPosition().x, 
					m_player->GetPosition().y + velocity);

				m_player->SetPosition(new_position);
        }
    }
}

void Game::Render()
{
	if(this->m_state == GAME_ACTIVE)
    {
        m_renderer->DrawSprite(
			ResourceManager::GetTexture("background"), 
            glm::vec2(0.0f, 0.0f), 
			glm::vec2(this->m_width, this->m_height), 
			0.0f);

		m_player->Draw(*m_renderer);
    }
}  
/*Methods-------------------------------------*/
/*Member methods*/
 
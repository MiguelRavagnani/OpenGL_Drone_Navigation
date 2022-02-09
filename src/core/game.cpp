#include "game.h"

#define GRAVITY 0

/*Constructors--------------------------------*/
Game::Game()
    
    : m_width (600),
      m_height (450),
	  m_tick (false) {}

Game::Game(
    unsigned int param_width, 
    unsigned int param_height)
    
    : m_width (param_width),
      m_height (param_height),
	  m_tick (false) {}

Game::~Game()
{
    delete m_player;
	delete m_renderer;
	delete m_sheet_renderer;
	delete m_screen_colision;
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
	m_sheet_renderer = new SpriteSheetRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("../textures/drone_frame.png", true, "player");
	ResourceManager::LoadTexture("../textures/drone_still.png", true, "player_still");
	ResourceManager::LoadTexture("../textures/bg_2.png", true, "background");

	glm::vec2 player_sheet_size((m_width / 8.0f) * 1.0f, (m_width / 8.0f) * 1.0f * 5.0f);
	glm::vec2 player_sprite_size((m_width / 8.0f) * 1.0f, (m_width / 8.0f) * 1.0f);

	glm::vec2 player_initial_velocity(1.0f, 1.0f);

	glm::vec3 player_color(1.0f);

	glm::vec2 player_inital_position = glm::vec2(
        m_width / 2.0f - player_sheet_size.x / 2.0f, 
        m_height - player_sheet_size.y);

	m_player = new GameObject(
		player_inital_position, 
		player_sheet_size,
		player_sprite_size,
		ResourceManager::GetTexture("player"),
		player_color,
		player_initial_velocity);

	m_player->SetMaxRotation(45.0f);

	GLfloat colision_height_percentage = (1.0f / 7.0f);

	m_screen_colision = new ScreenColision(
        this->m_width, 
        this->m_height, 
        colision_height_percentage,
		(m_width / 8.0f));

	m_state = GAME_ACTIVE;
}

void Game::Update(bool param_tick)
{
	m_floor_colision = m_screen_colision->DetectColisionY(m_player->GetPosition());
	m_tick = param_tick;
	std::cout << "Position Y: " << m_player->GetPosition().y << std::endl;
}

void Game::ProcessInput(GLfloat param_delta_time)
{
    if (this->m_state == GAME_ACTIVE)
    {
        GLfloat velocity = m_player->GetVelocity().x * param_delta_time; 
		glm::vec2 new_position;

        if (this->m_keys[GLFW_KEY_A])
        {
            if (m_player->GetPosition().x >= 0.0f)
            {
				new_position = glm::vec2(
					m_player->GetPosition().x - velocity, 
					m_player->GetPosition().y);

				m_player->SetPosition(new_position);
			}
        }

        if (this->m_keys[GLFW_KEY_D])
        {
            if (m_player->GetPosition().x <= this->m_width - m_player->GetSpriteSize().x)
			{
				new_position = glm::vec2(
					m_player->GetPosition().x + velocity, 
					m_player->GetPosition().y);

				m_player->SetPosition(new_position);
			}
        }

		if (this->m_keys[GLFW_KEY_W])
        {
            if (m_player->GetPosition().y >= 0.0f)
			{
				new_position = glm::vec2(
					m_player->GetPosition().x, 
					m_player->GetPosition().y - velocity);

				m_player->SetPosition(new_position);
			}
        }

#if !GRAVITY
        if (this->m_keys[GLFW_KEY_S])
        {
            if (!m_floor_colision)
			{
				new_position = glm::vec2(
					m_player->GetPosition().x, 
					m_player->GetPosition().y + velocity);

				m_player->SetPosition(new_position);
			}
			
        }
#endif
		if (this->m_keys[GLFW_KEY_Q])
        {
            if (m_player->GetRotation() >= -1.0f * (m_player->GetMaxRotation()))
			{
				m_player->SetRotation((m_player->GetRotation() - 2.0f / param_delta_time * DEG_TO_RAD));
			}
        }

		if (this->m_keys[GLFW_KEY_E])
        {
            if (m_player->GetRotation() <= (m_player->GetMaxRotation()))
			{
				m_player->SetRotation((m_player->GetRotation() + 2.0f / param_delta_time * DEG_TO_RAD));
			}
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

		if (!m_floor_colision)
		{
			glm::vec2 player_sheet_size((this->m_width / 8.0f), (this->m_width / 8.0f) * 5.0f);
			glm::vec2 player_sprite_size((this->m_width / 8.0f), (this->m_width / 8.0f));

			m_player->SetSize(player_sheet_size);

			m_player->SetSprite(ResourceManager::GetTexture("player"));
			m_player->SetSpriteSize(player_sprite_size);
			m_player->Draw(*this->m_sheet_renderer, m_tick);
		}
		else
		{
			glm::vec2 player_sprite_size((this->m_width / 8.0f) * 1.0f, (this->m_width / 8.0f) * 1.0f);

			m_player->SetSize(player_sprite_size);

			m_player->SetSprite(ResourceManager::GetTexture("player_still"));
			m_player->SetSpriteSize(player_sprite_size);
			m_player->Draw(*this->m_renderer);
		}
    }
}  
/*Methods-------------------------------------*/
/*Member methods*/
 
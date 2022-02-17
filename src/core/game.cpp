#include "game.h"

#define GRAVITY 1

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
	delete m_waypoint;
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
	ResourceManager::LoadTexture("../textures/waypoint_1.png", true, "waypoint");
	ResourceManager::LoadTexture("../textures/drone_still.png", true, "player_still");
	ResourceManager::LoadTexture("../textures/bg_2.png", true, "background");

	glm::vec2 player_sheet_size((m_width / 8.0f) * 1.0f, (m_width / 8.0f) * 1.0f * 5.0f);
	glm::vec2 player_sprite_size((m_width / 8.0f) * 1.0f, (m_width / 8.0f) * 1.0f);

	glm::vec2 player_initial_velocity(100.0f, 100.0f);

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

	m_waypoint = new GameObject(
		glm::vec2(m_width - 100.0f),
		glm::vec2(m_width / 8.0f),
		glm::vec2(m_width / 8.0f),
		ResourceManager::GetTexture("waypoint"),
		glm::vec3(1.0f),
		glm::vec2(0.0f));

	m_player->SetMaxRotation(45.0f);

	GLfloat colision_height_percentage = (1.0f / 16.0f);

	std::cout << m_height - colision_height_percentage * m_height << std::endl;

	m_screen_colision = new ScreenColision(
        this->m_width, 
        this->m_height, 
        colision_height_percentage,
		(m_width / 8.0f));

	m_drone_model = new Model(
        15000.0f,
        0.25f,
        9.81f * -100.0f,
        0.1f,
        0.0000001744f / 1.5f,
        0.0002f,
        0.005,
        0.006f);

	m_player->SetDroneModel(m_drone_model);

	m_player->m_drone_model->Drone_SetStateMotorSpeed1(0.0f);
	m_player->m_drone_model->Drone_SetStateMotorSpeed2(0.0f);
	m_player->m_drone_model->Drone_SetStatePosition1(340.0f);
	m_player->m_drone_model->Drone_SetStatePosition2(100.0f);
	m_player->m_drone_model->Drone_SetStateLinearSpeed1(0.0f);
	m_player->m_drone_model->Drone_SetStateLinearSpeed2(0.0f);
	m_player->m_drone_model->Drone_SetStatePhi(0.0f);
	m_player->m_drone_model->Drone_SetStateAngularVelocity(0.0f);

	m_state = GAME_ACTIVE;
}

void Game::Update(bool param_tick)
{
	m_floor_colision = m_screen_colision->DetectColisionY(m_player->GetPosition());
	m_tick = param_tick;
	std::cout << "Position Y: " << m_player->GetPosition().y << std::endl;
}

void Game::SetMouseClick(glm::vec2 param_mouse_click)
{
	m_mouse_click_position = param_mouse_click;
}

glm::vec2 Game::GetMouseClick()
{
	return m_mouse_click_position;
}

void Game::ProcessInput(GLfloat param_delta_time)
{
    if (this->m_state == GAME_ACTIVE)
    {

		if (this->m_keys[GLFW_KEY_E])
        {
			m_player->m_drone_model->Drone_SetStateMotorSpeed2(1000);
        }
		if (this->m_keys[GLFW_KEY_Q])
        {
			m_player->m_drone_model->Drone_SetStateMotorSpeed1(1000);
        }

		if (this->m_keys[GLFW_MOUSE_BUTTON_LEFT])
		{
			GLfloat x_offset;
			GLfloat y_offset;

			x_offset = 0.0f;//(32.0f * 3.0f / 2.0f);
			y_offset = 0.0f;//(32.0f * 3.0f / 2.0f);

			m_waypoint->SetPosition(glm::vec2(GLfloat(this->GetMouseClick().x) - x_offset, GLfloat(this->GetMouseClick().y) - y_offset));
			m_player->m_drone_model->Control_SetWaypoint(this->m_mouse_click_position);
			m_player->m_drone_model->Control_CalculateError();

			GLfloat kp = 0.5f;;

			std::vector<GLfloat> initial_command {
				m_player->m_drone_model->Control_GetError().x * -kp, 
				m_player->m_drone_model->Control_GetError().y * kp};

			// m_player->m_drone_model->Drone_SetCommand(initial_command);
		}

		m_player->m_drone_model->SetDeltaTime(param_delta_time);
		glm::vec2 new_position(
			m_player->m_drone_model->Drone_GetStateVector()[2],
			m_player->m_drone_model->Drone_GetStateVector()[3]);
		
		m_player->SetPosition(new_position);

		if (Math::Conversion::RadiansToDegrees(m_player->m_drone_model->Drone_GetStateVector()[6]) >= 360.0f || 
		    Math::Conversion::RadiansToDegrees(m_player->m_drone_model->Drone_GetStateVector()[6]) <= -360.0f)
		{
			m_player->m_drone_model->Drone_SetStatePhi(0.0f);
		}

		Physics::FourthOrder::UpdatePhysics(m_player->m_drone_model);
		// std::cout << "Calculated w1: " << m_player->m_drone_model->Drone_GetStateVector()[0] << std::endl;
		// std::cout << "Calculated w2: " << m_player->m_drone_model->Drone_GetStateVector()[1] << std::endl;
		// std::cout << "Calculated r1: " << m_player->m_drone_model->Drone_GetStateVector()[2] << std::endl;
		// std::cout << "Calculated r2: " << m_player->m_drone_model->Drone_GetStateVector()[3] << std::endl;
		// std::cout << "Calculated v1: " << m_player->m_drone_model->Drone_GetStateVector()[4] << std::endl;
		// std::cout << "Calculated v2: " << m_player->m_drone_model->Drone_GetStateVector()[5] << std::endl;
		// std::cout << "Calculated phi: " << Math::Conversion::RadiansToDegrees(m_player->m_drone_model->Drone_GetStateVector()[6]) << std::endl;
		// std::cout << "Calculated omega: " << (m_player->m_drone_model->Drone_GetStateVector()[7]) << std::endl;

		m_player->SetRotation(Math::Conversion::RadiansToDegrees(m_player->m_drone_model->Drone_GetStateVector()[6]));

		bool impact = false;

		if (m_floor_colision && (m_drone_model->Drone_GetGravity() == 0.0f))
			impact = true;

		if (m_floor_colision)
		{
			if (!impact)
			{
				m_drone_model->Drone_SetGravity(0.0f);
				m_drone_model->Drone_SetStateLinearSpeed2(0.0f);
			}
		}
		else
		{
			if (m_drone_model->Drone_GetGravity() == 0.0f)
			{
				m_drone_model->Drone_SetGravity(9.81f * -100.0f);
			}
		}
	}
}

void Game::Render()
{
	if(this->m_state == GAME_ACTIVE)
    {
        m_renderer->DrawBackground(
			ResourceManager::GetTexture("background"), 
            glm::vec2(0.0f, 0.0f), 
			glm::vec2(this->m_width, this->m_height), 
			0.0f);
		
		m_waypoint->Draw(*this->m_renderer);

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
 
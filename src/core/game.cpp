#include "game.h"

#define GRAVITY 1
#define G_CONST 1.0f

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
	delete m_button_automatic;
	delete m_button_manual;
	delete m_button_menu;
	delete m_button_menu_close;
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
	ResourceManager::LoadTexture("../textures/button_automatic.png", true, "button_automatic");
	ResourceManager::LoadTexture("../textures/button_manual.png", true, "button_manual");
	ResourceManager::LoadTexture("../textures/button_menu.png", true, "button_menu");
	ResourceManager::LoadTexture("../textures/button_menu_close.png", true, "button_menu_close");
	ResourceManager::LoadTexture("../textures/waypoint_1.png", true, "waypoint");
	ResourceManager::LoadTexture("../textures/drone_still.png", true, "player_still");
	ResourceManager::LoadTexture("../textures/bg_2.png", true, "background");

	glm::vec2 player_sheet_size((m_width / 8.0f), (m_width / 8.0f)* 5.0f);
	glm::vec2 player_sprite_size((m_width / 8.0f), (m_width / 8.0f));

	glm::vec2 player_initial_velocity(100.0f, 100.0f);

	glm::vec3 player_color(1.0f);

	glm::vec2 player_inital_position = glm::vec2(
        m_width / 2.0f + player_sheet_size.x / 2.0f, 
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
	
	glm::vec2 button_size(m_width * 3.0f / 8.0f, (m_width/ 8.0f));
	glm::vec2 button_automatic_position(m_width / 2.0f, m_height * 0.60f);
	glm::vec2 button_manual_position(m_width / 2.0f, m_height * 0.30f);
	glm::vec2 m_button_menu_position(m_width * 0.04f, m_height * 0.055f);

	m_button_automatic = new GameObject(
		button_automatic_position,
		button_size,
		button_size,
		ResourceManager::GetTexture("button_automatic"),
		glm::vec3(1.0f),
		glm::vec2(0.0f));

	m_button_manual = new GameObject(
		button_manual_position,
		button_size,
		button_size,
		ResourceManager::GetTexture("button_manual"),
		glm::vec3(1.0f),
		glm::vec2(0.0f));

	m_button_menu = new GameObject(
		m_button_menu_position,
		glm::vec2(m_width / 16.0f),
		glm::vec2(m_width / 16.0f),
		ResourceManager::GetTexture("button_menu"),
		glm::vec3(1.0f),
		glm::vec2(0.0f));

	m_button_menu_close = new GameObject(
		m_button_menu_position,
		glm::vec2(m_width / 16.0f),
		glm::vec2(m_width / 16.0f),
		ResourceManager::GetTexture("button_menu_close"),
		glm::vec3(1.0f),
		glm::vec2(0.0f));

	m_player->SetMaxRotation(45.0f);

	GLfloat colision_height_percentage = (1.0f / 16.0f);

	// std::cout << m_height - colision_height_percentage * m_height << std::endl;

	m_screen_colision = new ScreenColision(
        this->m_width, 
        this->m_height, 
        colision_height_percentage,
		(m_width / 8.0f));

	m_drone_model = new Model(
        15000.0f,
        0.25f,
        9.81f,
        0.1f,
        0.0000001744f,
        0.0002f,
        0.005,
        0.006f,
		5000.0f);

	m_player->SetDroneModel(m_drone_model);

	m_player->m_drone_model->Drone_SetStateMotorSpeed1(0.0f);
	m_player->m_drone_model->Drone_SetStateMotorSpeed2(0.0f);
	m_player->m_drone_model->Drone_SetStatePosition1(m_width / 2.0f);
	m_player->m_drone_model->Drone_SetStatePosition2(m_height * 0.78f);
	m_player->m_drone_model->Drone_SetStateLinearSpeed1(0.0f);
	m_player->m_drone_model->Drone_SetStateLinearSpeed2(0.0f);
	m_player->m_drone_model->Drone_SetStatePhi(0.0f);
	m_player->m_drone_model->Drone_SetStateAngularVelocity(0.0f);
	
	this->m_loop = GAME_MENU;
	this->m_state = GAME_ACTIVE;
}

void Game::Update(bool param_tick)
{
	m_floor_colision = m_screen_colision->DetectColisionY(m_player->GetPosition());
	m_tick = param_tick;
	// std::cout << "Position Y: " << m_player->GetPosition().y << std::endl;
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
		switch (this->m_loop)
		{
		case GAME_MENU:
			{
				if (this->m_keys[GLFW_MOUSE_BUTTON_LEFT])
				{
					if (m_button_manual->BoudingBox(this->GetMouseClick()))
					{
						std::cout << "Manual" << std::endl;
						m_player->m_drone_model->Drone_SetStateMotorSpeed1(0.0f);
						m_player->m_drone_model->Drone_SetStateMotorSpeed2(0.0f);
						m_player->m_drone_model->Drone_SetStatePosition1(m_width / 2.0f);
						m_player->m_drone_model->Drone_SetStatePosition2(m_height * 0.78f);
						m_player->m_drone_model->Drone_SetStateLinearSpeed1(0.0f);
						m_player->m_drone_model->Drone_SetStateLinearSpeed2(0.0f);
						m_player->m_drone_model->Drone_SetStatePhi(0.0f);
						m_player->m_drone_model->Drone_SetStateAngularVelocity(0.0f);
						std::vector<GLfloat> initial_command {0.0f, 0.0f};
						m_player->m_drone_model->Drone_SetCommand(initial_command);
						this->m_loop = GAME_LOOP_MANUAL;
						m_is_waypoint = false;
					}
					
					else if (m_button_automatic->BoudingBox(this->GetMouseClick()))
					{
						std::cout << "Automatic" << std::endl;
						this->m_loop = GAME_LOOP_AUTOMATIC;
						m_player->m_drone_model->Drone_SetStateMotorSpeed1(0.0f);
						m_player->m_drone_model->Drone_SetStateMotorSpeed2(0.0f);
						m_player->m_drone_model->Drone_SetStatePosition1(m_width / 2.0f);
						m_player->m_drone_model->Drone_SetStatePosition2(m_height * 0.78f);
						m_player->m_drone_model->Drone_SetStateLinearSpeed1(0.0f);
						m_player->m_drone_model->Drone_SetStateLinearSpeed2(0.0f);
						m_player->m_drone_model->Drone_SetStatePhi(0.0f);
						m_player->m_drone_model->Drone_SetStateAngularVelocity(0.0f);
					}

					else if (m_button_menu_close->BoudingBox(this->GetMouseClick()))
					{
						std::cout << "Close menu" << std::endl;
						this->m_loop = GAME_LOOP_AUTOMATIC;
					}
				}
				this->m_keys[GLFW_MOUSE_BUTTON_LEFT] = false;
				break;
			}

		case GAME_LOOP_MANUAL:
			{
				if (this->m_keys[GLFW_MOUSE_BUTTON_LEFT])
				{
					if (m_button_menu->BoudingBox(this->GetMouseClick()))
					{
						std::cout << "Open Menu" << std::endl;
						this->m_loop = GAME_MENU;
						this->m_keys[GLFW_MOUSE_BUTTON_LEFT] = false;
						break;
					}
				}
				m_player->m_drone_model->SetControlled(false);
				if (this->m_keys[GLFW_KEY_E])
				{
					m_increment = m_player->m_drone_model->Drone_GetStateMotorSpeed2();
					
					m_player->m_drone_model->Drone_SetStateMotorSpeed2((7000.0f));
					m_player->m_drone_model->SetControlled(true);
				}
				if (this->m_keys[GLFW_KEY_Q])
				{
					m_player->m_drone_model->Drone_SetStateMotorSpeed1(7000.0f);
					m_player->m_drone_model->SetControlled(true);
				}
				std::cout << "W1: " << m_player->m_drone_model->Drone_GetStateMotorSpeed1() << " W2: " << m_player->m_drone_model->Drone_GetStateMotorSpeed2() << std::endl;
				break;
			}

		case GAME_LOOP_AUTOMATIC:
			{
				if (this->m_keys[GLFW_MOUSE_BUTTON_LEFT])
				{
					if (m_button_menu->BoudingBox(this->GetMouseClick()))
					{
						std::cout << "Open Menu" << std::endl;
						this->m_loop = GAME_MENU;
						this->m_keys[GLFW_MOUSE_BUTTON_LEFT] = false;
						m_is_waypoint = false;
						break;
					}
				}
				if (this->m_keys[GLFW_MOUSE_BUTTON_LEFT])
				{
					GLfloat x_offset;
					GLfloat y_offset;

					x_offset = 0.0f;//(32.0f * 3.0f / 2.0f);
					y_offset = 0.0f;//(32.0f * 3.0f / 2.0f);

					m_waypoint->SetPosition(glm::vec2(GLfloat(this->GetMouseClick().x) - x_offset, GLfloat(this->GetMouseClick().y) - y_offset));
					m_player->m_drone_model->Control_SetWaypoint(this->m_mouse_click_position);
					m_player->m_drone_model->Control_CalculatePositionError();

					m_is_waypoint = true;

					GLfloat kp = 0.5f;
					this->m_keys[GLFW_MOUSE_BUTTON_LEFT] = false;
				}
				else
				{
					std::vector<GLfloat> initial_command {0.0f, 0.0f};
					m_player->m_drone_model->Drone_SetCommand(initial_command);
				}
				if (m_is_waypoint)
				{
					std::vector<GLfloat> initial_command {0.0f, 0.0f};

					initial_command = m_player->m_drone_model->Control_System(m_player->m_drone_model->Drone_GetStateVector());

					std::cout << "Control force w1: " << initial_command[0] << " | Control force w2: " << initial_command[1] << std::endl;

					m_player->m_drone_model->Drone_SetCommand(initial_command);

				}
				break;
			}
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
		std::cout << "Calculated omega: " << (m_player->m_drone_model->Drone_GetStateVector()[7]) << std::endl;

		m_player->SetRotation(Math::Conversion::RadiansToDegrees(m_player->m_drone_model->Drone_GetStateVector()[6]));

		bool impact = false;

		if (m_floor_colision)
		{
			if (true)
			{
				if (m_player->m_drone_model->Drone_GetStateLinearSpeed2() >= 0.0f)
				{
					m_player->m_drone_model->Drone_SetStateLinearSpeed2(0.0f);
				}
			}
			std::cout << "y speed: " << m_player->m_drone_model->Drone_GetStateLinearSpeed2() << std::endl;
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
		
		switch (this->m_loop)
		{
		case GAME_MENU:
			{
				/* Render menu */
				m_button_automatic->Draw(*this->m_renderer);
				m_button_manual->Draw(*this->m_renderer);
				m_button_menu_close->Draw(*this->m_renderer);
				break;
			}

		case GAME_LOOP_MANUAL:
			{
				m_button_menu->Draw(*this->m_renderer);

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
				break;
			}

		case GAME_LOOP_AUTOMATIC:
			{
				m_button_menu->Draw(*this->m_renderer);
				
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
				m_waypoint->Draw(*this->m_renderer);
				break;
			}
		}
		

    }
}
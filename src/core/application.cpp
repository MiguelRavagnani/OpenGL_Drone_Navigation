#include "application.h"

std::function<void()> registered_loop;
void loop_iteration() {
    registered_loop();
}

Application::Application(
        unsigned int param_screen_width,
        unsigned int param_screen_height)
        : m_screen_width (param_screen_width),
          m_screen_height (param_screen_height) 
{
    m_drone = new Game(m_screen_width, m_screen_height);
}

Application::~Application() {}

void Application::Run()
{
    Input &callback = Input::GetInstance();
    callback.SetGameInstance(m_drone);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(m_screen_width, m_screen_height, "Drone", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetKeyCallback(window, callback.key_callback);
    glfwSetMouseButtonCallback(window, callback.mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, callback.framebuffer_size_callback);

    glViewport(0, 0, m_screen_width, m_screen_height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_drone->Init();

    GLfloat delta_time = 0.0f;
    GLfloat delta_last_time = 0.0f;

    GLfloat last_sprite_frame_time = 0.0f;

    emscripten_set_main_loop(loop_iteration, 0, 1);

    registered_loop = [&]()
    {

        GLfloat delta_current_time = glfwGetTime();
        GLfloat current_sprite_frame_time = glfwGetTime();
        
        bool tick = false;

        delta_time = delta_current_time - delta_last_time;
        delta_last_time = delta_current_time;

        std::stringstream FPS(std::stringstream::in | std::stringstream::out);
        FPS << std::fixed << std::setprecision(2) << (1.0f / delta_time);
        
        std::stringstream milisseconds(std::stringstream::in | std::stringstream::out);
        milisseconds << std::fixed << std::setprecision(2) << (delta_time * 1000.0f);

        std::stringstream FPS_title(std::stringstream::in | std::stringstream::out);
        FPS_title << "Drone Simulation - FPS: "
                  << FPS.str()
                  << " | Milisseconds: "
                  << milisseconds.str();
            
        glfwSetWindowTitle(window, FPS_title.str().c_str());

        if (current_sprite_frame_time - last_sprite_frame_time >= 0.075f)
        {
            last_sprite_frame_time = current_sprite_frame_time;

            tick = true;
        }

        glfwPollEvents();

        m_drone->ProcessInput(delta_time);
        m_drone->Update(tick);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_drone->Render();

        glfwSwapBuffers(window);
    };

    ResourceManager::Clear();

    glfwTerminate();
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <functional>

#ifdef __EMSCRIPTEN__
#include <emscripten.h> 
#include <emscripten/html5.h>
#include <cmath>
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

std::function<void()> registered_loop;

void loop_iteration() {
	registered_loop();
}

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Game Drone(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
    glfwInit();
   
#ifdef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Drone", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Drone.Init();

    GLfloat delta_time = 0.0f;
    GLfloat delta_last_time = 0.0f;

    GLfloat last_sprite_frame_time = 0.0f;

#ifdef __EMSCRIPTEN__
      emscripten_set_main_loop(loop_iteration, 0, 1);
#else
      while (!glfwWindowShouldClose(window)) {
        loop_iteration();
           }
      glfwTerminate();
#endif

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

        Drone.ProcessInput(delta_time);
        Drone.Update(tick);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Drone.Render();

        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop_iteration, 0, 1);
#else
    while (!glfwWindowShouldClose(window))
    {
        loop_iteration();
    }
    glfwTerminate();
#endif
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Drone.m_keys[key] = true;
        else if (action == GLFW_RELEASE)
            Drone.m_keys[key] = false;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double x_position;
        double y_position;

        glfwGetCursorPos(window, &x_position, &y_position);

        if (action == GLFW_PRESS)
            Drone.m_keys[button] = true;
        else if (action == GLFW_RELEASE)
            Drone.m_keys[button] = false;

        Drone.SetMouseClick(glm::vec2(x_position, y_position));
        // std::cout << "Cursor x: " << x_position << " Cursor y: " << y_position << "" <<std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
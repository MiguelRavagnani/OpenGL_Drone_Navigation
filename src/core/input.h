#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"

class Input 
{
public:
    /**
     * @brief Get the Instance object singleton
     * 
     * @return Input& Lazy Singleton
     */
    static Input& GetInstance()
    {
        static Input instance;
        return instance;
    }

    /**
     * @brief Set the Game Instance object
     * 
     * @param param_game Game instance
     */
    void SetGameInstance(Game *param_game)
    {
        GetInstance().m_game_instance = param_game;
    }

    /**
     * @brief GLViewport frame size callback
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        GetInstance().KeyCallbackImplementation(window, key, scancode, action, mode);
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        GetInstance().MouseButtonCallbackImplementation(window, button, action, mods); 
    }

    void MouseButtonCallbackImplementation(GLFWwindow* window, int button, int action, int mods) //this is the actual implementation of the callback method
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            double x_position;
            double y_position;

            glfwGetCursorPos(window, &x_position, &y_position);

            if (action == GLFW_PRESS)
                GetInstance().m_game_instance->m_keys[button] = true;
            else if (action == GLFW_RELEASE)
                GetInstance().m_game_instance->m_keys[button] = false;

            GetInstance().m_game_instance->SetMouseClick(glm::vec2(x_position, y_position));
        }
    }

    void KeyCallbackImplementation(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (key >= 0 && key < 1024)
        {
        if (action == GLFW_PRESS)
            GetInstance().m_game_instance->m_keys[key] = true;
        else if (action == GLFW_RELEASE)
            GetInstance().m_game_instance->m_keys[key] = false;
    }

    }

private:
    /**
     * @brief Construct a new Input object. The private
     *        nature prevents more than one instance
     */
    Input(void)
    {
        m_game_instance = new Game();
    }

    /**
     * @brief Prevents coppies
     */
    Input(Input const&);

    /**
     * @brief Prevents assignments
     */
    void operator=(Input const&);

    Game *m_game_instance;
};



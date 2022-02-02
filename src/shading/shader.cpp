#include "shader.h"

#include <iostream>

Shader &Shader::Use()
{
    glUseProgram(this->m_texture_ID);
    return *this;
}

void Shader::Compile(
    const char* param_vertex_source, 
    const char* param_fragment_source, 
    const char* param_geometry_source)
{
    GLuint vertex_shader;
    GLuint fragment_shader; 
    GLuint geometry_shader;

    /* Setting up the fragment shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &param_vertex_source, NULL);
    glCompileShader(vertex_shader);

    CheckCompileErrors(vertex_shader, "VERTEX");

    /* Setting up the fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &param_fragment_source, NULL);
    glCompileShader(fragment_shader);

    CheckCompileErrors(fragment_shader, "FRAGMENT");

    /* Compile geometry shader if exists */
    if (param_geometry_source != nullptr)
    {
        geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);

        glShaderSource(geometry_shader, 1, &param_geometry_source, NULL);
        glCompileShader(geometry_shader);

        CheckCompileErrors(geometry_shader, "GEOMETRY");
    }

    /* Shader program */
    this->m_texture_ID = glCreateProgram();

    glAttachShader(this->m_texture_ID, vertex_shader);
    glAttachShader(this->m_texture_ID, fragment_shader);

    if (param_geometry_source != nullptr)
    {
        glAttachShader(this->m_texture_ID, geometry_shader);
    }

    glLinkProgram(this->m_texture_ID);
    CheckCompileErrors(this->m_texture_ID, "PROGRAM");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if (param_geometry_source != nullptr)
    {
        glDeleteShader(geometry_shader);
    }
}

void Shader::SetFloat(
    const char *param_name, 
    GLfloat param_value, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform1f(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_value);
}

void Shader::SetInteger(
    const char *param_name, 
    GLint param_value, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform1i(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_value);
}

void Shader::SetVector2f(
    const char *param_name, 
    GLfloat param_x, 
    GLfloat param_y, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform2f(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_x, 
        param_y);
}

void Shader::SetVector2f(
    const char *param_name, 
    const glm::vec2 &param_value, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform2f(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_value.x, 
        param_value.y);
}

void Shader::SetVector3f(
    const char *param_name, 
    GLfloat param_x, 
    GLfloat param_y, 
    GLfloat param_z, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform3f(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_x, 
        param_y, 
        param_z);
}

void Shader::SetVector3f(
    const char *param_name, 
    const glm::vec3 &param_value, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform3f(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_value.x, 
        param_value.y, 
        param_value.z);
}

void Shader::SetVector4f(
    const char *param_name, 
    GLfloat param_x, 
    GLfloat param_y, 
    GLfloat param_z, 
    GLfloat param_w, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform4f(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_x, 
        param_y, 
        param_z, 
        param_w);
}

void Shader::SetVector4f(
    const char *param_name, 
    const glm::vec4 &param_value, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }

    glUniform4f(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        param_value.x, 
        param_value.y, 
        param_value.z, 
        param_value.w);
}

void Shader::SetMatrix4(
    const char *param_name, 
    const glm::mat4 &matrix, 
    bool param_use_shader)
{
    if (param_use_shader)
    {
        this->Use();
    }
    
    glUniformMatrix4fv(
        glGetUniformLocation(this->m_texture_ID, param_name), 
        1, 
        false, 
        glm::value_ptr(matrix));
}

void Shader::CheckCompileErrors(
    GLuint param_object, 
    std::string param_type)
{
    GLint success;
    char infoLog[1024];
    if (param_type != "PROGRAM")
    {
        glGetShaderiv(param_object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(param_object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << param_type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(param_object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(param_object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << param_type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
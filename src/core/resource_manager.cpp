#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader ResourceManager::LoadShader(
    const char *param_vertex_shader_file, 
    const char *param_fragment_shader_file, 
    const char *param_geometry_shader_file, 
    std::string param_name)
{
    Shaders[param_name] = LoadShaderFromFile(param_vertex_shader_file, param_fragment_shader_file, param_geometry_shader_file);
    return Shaders[param_name];
}

Shader ResourceManager::GetShader(std::string param_name)
{
    return Shaders[param_name];
}

Texture2D ResourceManager::LoadTexture(
    const char *param_file, 
    bool param_alpha, 
    std::string param_name)
{
    Textures[param_name] = LoadTextureFromFile(param_file, param_alpha);
    return Textures[param_name];
}

Texture2D ResourceManager::GetTexture(std::string param_name)
{
    return Textures[param_name];
}

void ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.m_texture_ID);
        
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.m_texture_ID);
}

Shader ResourceManager::LoadShaderFromFile(
    const char *param_vertex_shader_file, 
    const char *param_fragment_shader_file, 
    const char *param_geometry_shader_file)
{
    std::string vertex_code;
    std::string fragment_code;
    std::string geometry_code;
    try
    {
        std::ifstream vertex_shader_file(param_vertex_shader_file);
        std::ifstream fragment_shader_file(param_fragment_shader_file);
        std::stringstream vertex_shader_stream;
        std::stringstream fragment_shader_stream;
        
        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();
        
        vertex_shader_file.close();
        fragment_shader_file.close();
        
        vertex_code = vertex_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
        
        if (param_geometry_shader_file != nullptr)
        {
            std::ifstream geometry_shader_file(param_geometry_shader_file);
            std::stringstream geometry_shader_stream;

            geometry_shader_stream << geometry_shader_file.rdbuf();
            geometry_shader_file.close();
            geometry_code = geometry_shader_stream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertex_code.c_str();
    const char *fShaderCode = fragment_code.c_str();
    const char *gShaderCode = geometry_code.c_str();
    
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, param_geometry_shader_file != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const char *param_file, bool param_alpha)
{
    Texture2D texture;
    if (param_alpha)
    {
        texture.m_internal_format = GL_RGBA;
        texture.m_image_format = GL_RGBA;
    }
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load(param_file, &width, &height, &nrChannels, 0);
    
    texture.Generate(width, height, data);
    
    stbi_image_free(data);
    return texture;
}
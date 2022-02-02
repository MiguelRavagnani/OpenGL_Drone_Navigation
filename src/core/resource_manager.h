#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

/** 
 *  @file   resource_manager.h 
 *  @brief  TODO: Fill
 *  @date   2022-30-01  
 **************************************************/

/**
 * @brief TODO: Fill
 */

class ResourceManager
{
private:

    /*Constructors--------------------------------*/
    /**
     * @brief ResourceManager constructor
     */
    ResourceManager(){}
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_vertex_shader_file ...
     * @param param_fragment_shader_file ...
     * @param param_geometry_shader_file ...
     */
    static Shader LoadShaderFromFile(
        const char *param_vertex_shader_file, 
        const char *param_fragment_shader_file, 
        const char *param_geometry_shader_file = nullptr);
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_file ...
     * @param param_alpha ...
     */
    static Texture2D LoadTextureFromFile(
        const char *param_file, 
        bool param_alpha);
    
public:

    /**
     * @brief TODO: Fill
     * 
     * @param param_vertex_shader_file ...
     * @param param_fragment_shader_file ...
     * @param param_geometry_shader_file ...
     * @param param_name ...
     */
    static Shader LoadShader(
        const char *param_vertex_shader_file, 
        const char *param_fragment_shader_file, 
        const char *param_geometry_shader_file, 
        std::string param_name);

    /**
     * @brief TODO: Fill
     * 
     * @param param_name ...
     */
    static Shader GetShader(std::string param_name);
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_file ...
     * @param param_alpha ...
     * @param param_name ...
     */
    static Texture2D LoadTexture(
        const char *param_file, 
        bool param_alpha, 
        std::string param_name);
        
    /**
     * @brief TODO: Fill
     * 
     * @param param_name ...
     */
    static Texture2D GetTexture(std::string param_name);

    /**
     * @brief TODO: Fill
     */
    static void Clear();

    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures; 
};

#endif // _RESOURCE_MANAGER_H_
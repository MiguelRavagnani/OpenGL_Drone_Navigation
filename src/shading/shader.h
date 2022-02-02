
#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/** 
 *  @file   shader.h 
 *  @brief  TODO: Fill
 *  @date   2022-30-01  
 **************************************************/

/**
 * @brief TODO: Fill
 */

class Shader
{
public:

    /*Constructors--------------------------------*/

    /**
     * @brief Shader constructor
     */
    Shader(){}

    /*Methods-------------------------------------*/
    /*Member methods*/

    /**
     * @brief TODO: Fill
     */
    Shader &Use();
    
    /**
     * @brief TODO: Fill
     * 
     * @param param_vertex_source ...
     * @param param_fragment_source ...
     * @param param_geometry_source ...
     */
    void Compile(
        const char *param_vertex_source, 
        const char *param_fragment_source, 
        const char *param_geometry_source = nullptr);
    
    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a GLfloat value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_value Points to a null terminated string containing 
     *                    the name of the uniform variable whose location 
     *                    is to be queried
     * @param param_use_shader Shader to be used
     */
    void SetFloat(
        const char *param_name, 
        GLfloat param_value, 
        bool param_use_shader = false);

    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a GLint value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_value Points to a null terminated string containing 
     *                    the name of the uniform variable whose location 
     *                    is to be queried
     * @param param_use_shader Shader to be used
     */
    void SetInteger(
        const char *param_name, 
        GLint param_value, 
        bool param_use_shader = false);

    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a float vector value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_x X value of the vector
     * @param param_y y value of the vector
     * @param param_use_shader Shader to be used
     */
    void SetVector2f(
        const char *param_name, 
        GLfloat param_x, 
        GLfloat param_y, 
        bool param_use_shader = false);

    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a vec2 float value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_value Vec2 of floats
     * @param param_use_shader Shader to be used
     */
    void SetVector2f(
        const char *param_name, 
        const glm::vec2 &param_value, 
        bool param_use_shader = false);

    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a float vector value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_x X value of the vector
     * @param param_y y value of the vector
     * @param param_z z value of the vector
     * @param param_use_shader Shader to be used
     */
    void SetVector3f(
        const char *param_name, 
        GLfloat param_x, 
        GLfloat param_y, 
        GLfloat param_z, 
        bool param_use_shader = false);

    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a vec3 float value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_value Vec3 of floats
     * @param param_use_shader Shader to be used
     */
    void SetVector3f(
        const char *param_name, 
        const glm::vec3 &param_value, 
        bool param_use_shader = false);

    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a float vector value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_x X value of the vector
     * @param param_y y value of the vector
     * @param param_z z value of the vector
     * @param param_w w value of the vector
     * @param param_use_shader Shader to be used
     */
    void SetVector4f(
        const char *param_name, 
        GLfloat param_x, 
        GLfloat param_y, 
        GLfloat param_z, 
        GLfloat param_w, 
        bool param_use_shader = false);

    /**
     * @brief Gets the location of a certain uniform variable in the
     *        member texture, and assings a vec4 float value to it
     * 
     * @param param_name Specifies the program object to be queried
     * @param param_value Vec4 of floats
     * @param param_use_shader Shader to be used
     */
    void SetVector4f(
        const char *param_name, 
        const glm::vec4 &param_value, 
        bool param_use_shader = false);

    /**
     * @brief TODO: Fill
     * 
     * @param param_name ...
     * @param param_matrix ...
     * @param param_use_shader ...
     */
    void SetMatrix4(
        const char *param_name, 
        const glm::mat4 &param_matrix, 
        bool param_use_shader = false);
        
    /*Variables-----------------------------------*/

    GLuint m_texture_ID;

private:

    /*Methods-------------------------------------*/

    /**
     * @brief TODO: Fill
     * 
     * @param param_object ...
     * @param param_type ...
     */
    void CheckCompileErrors(
        GLuint param_object, 
        std::string param_type);
};

#endif // _SHADER_H_
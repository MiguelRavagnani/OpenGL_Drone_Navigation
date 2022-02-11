#ifndef _MATH_UTILS_
#define _MATH_UTILS_

/** 
 *  @file   math_utils.h.h 
 *  @brief  Library description
 *  @date   2022-08-02 
 **************************************************/
#include <vector>

#include <glad/glad.h>

#define PI 3.14159265f

#include "model.h"

/**
 * @brief Math utility
 */
namespace Math
{
    namespace FourthOrder
    {
        struct State
        {

        };
        
        /**
         * @brief TODO: Fill
         * 
         * @param param_current_time ...
         * @param param_integration_step ...
         * @param param_current_state_vector ...
         * @param param_current_input_cmd ...
         * @param param_model ...
         * 
         * @return std::vector<GLfloat> ... 
         */
        std::vector<GLfloat> RungeKutta(
            std::vector<GLfloat> param_current_time,
            std::vector<GLfloat> param_integration_step,
            std::vector<GLfloat> param_current_state_vector,
            std::vector<GLfloat> param_current_input_cmd,
            Model* param_model);
    }

    namespace Conversion
    {
        /**
         * @brief Converts radians to  degrees
         * 
         * @param param_radians Value in radians
         * 
         * @return GLfloat Value in degrees
         */
        GLfloat RadiansToDegrees(GLfloat param_radians);

        /**
         * @brief Converts degrees to radians
         * 
         * @param param_degrees Value in degrees 
         * 
         * @return GLfloat Value in radians
         */
        GLfloat DegreesToRadians(GLfloat param_degrees);
    }
}

#endif //_MATH_UTILS_
 
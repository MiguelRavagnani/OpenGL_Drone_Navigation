#ifndef _DRONE_MODEL_
#define _DRONE_MODEL_

/** 
 *  @file   drone_model.h 
 *  @brief  Class description
 *  @date   YYYY-DD-MM 
 **************************************************/

#include <vector>
#include <math.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "math_utils.h"

/**
 * @brief Class description
 */
class DroneModel
{
public:
    /*Constructors--------------------------------*/
    /**
     * @brief DroneModel constructor
     */
    DroneModel();

    DroneModel(
        GLfloat param_max_motor_speed,
        GLfloat param_mass,
        GLfloat param_gravity_acc,
        GLfloat param_wing_lenght,
        GLfloat param_force_constant,
        GLfloat param_momentum_of_inercia,
        GLfloat param_tau,
        GLfloat param_integration_step);

    /**
     * @brief DroneModel desctructor
     */
    ~DroneModel();

    /*Methods-------------------------------------*/

    /**
     * @brief TODO: Fill
     * 
     * @param param_time ...
     * @param param_state_vector ...
     * @param param_input_cmd ...
     * 
     * @return std::vector<GLfloat> ...
     */
    std::vector<GLfloat> StateVectorModel(
        std::vector<GLfloat> param_time, 
        std::vector<GLfloat> param_state_vector, 
        std::vector<GLfloat> param_input_cmd);

private:
    /*--------------------------------------------*/
    
    /** @brief  w_max | default (15000)*/
    GLfloat m_max_motor_speed;

    /** @brief  m | default (0.25) kg*/
    GLfloat m_mass;

    /** @brief  g | default (9.81) m/s^2*/
    GLfloat m_gravity_acc;

    /** @brief  l | default (0.1) m*/
    GLfloat m_wing_lenght;

    /** @brief  kf | default (1.744e-8)*/
    GLfloat m_force_constant;

    /** @brief  Iz | default (2e-4)*/
    GLfloat m_momentum_of_inercia;

    /** @brief  tau | default (0.005)*/
    GLfloat m_tau;

    /* Integration step */
    GLfloat m_integration_step;

    std::vector<GLfloat> m_state_vector;
};

#endif //_DRONE_MODEL_
 
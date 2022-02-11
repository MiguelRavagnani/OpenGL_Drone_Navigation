#ifndef _DRONE_MODEL_
#define _DRONE_MODEL_

/** 
 *  @file   model.h 
 *  @brief  Class description
 *  @date   YYYY-DD-MM 
 **************************************************/

#include <vector>
#include <math.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

/**
 * @brief Class description
 */
class Model
{
public:
    /*--------------------------------------------*/
    /*              Generic                       */
    /*--------------------------------------------*/
    /**
     * @brief Generic Model Constructor
     */
    Model();

    /**
     * @brief Model desctructor
     */
    ~Model();

    /**
     * @brief Generic State Vector
     * 
     */
    std::vector<GLfloat> StateVector();

    /*--------------------------------------------*/
    /*              Drone Model                   */
    /*--------------------------------------------*/

    /**
     * @brief Drone Model Constructor
     * 
     * @param param_max_motor_speed ...
     * @param param_mass ...
     * @param param_gravity_acc ...
     * @param param_wing_lenght ...
     * @param param_force_constant ...
     * @param param_momentum_of_inercia ...
     * @param param_tau ...
     * @param param_integration_step ...
     */
    Model(
        GLfloat param_max_motor_speed,
        GLfloat param_mass,
        GLfloat param_gravity_acc,
        GLfloat param_wing_lenght,
        GLfloat param_force_constant,
        GLfloat param_momentum_of_inercia,
        GLfloat param_tau,
        GLfloat param_integration_step);

    /**
     * @brief Drone state vector
     * 
     * @param param_time ...
     * @param param_state_vector ...
     * @param param_input_cmd ...
     * 
     * @return std::vector<GLfloat> ...
     */
    std::vector<GLfloat> StateVector(
        std::vector<GLfloat> param_time, 
        std::vector<GLfloat> *param_state_vector, 
        std::vector<GLfloat> param_input_cmd);

    /**
     * @brief TODO: Fill
     * 
     */
    void UpdatePhysics();

    /**
     * @brief Set the State Motor Speed object
     * 
     * @param param_w1 ...
     */
    void SetStateMotorSpeed1(GLfloat param_w1);

    /**
     * @brief Set the State Motor Speed object
     * 
     * @param param_w2 ...
     */
    void SetStateMotorSpeed2(GLfloat param_w2);

    /**
     * @brief Set the State Position object
     * 
     * @param param_r1 ...
     */
    void SetStatePosition1(GLfloat param_r1);

    /**
     * @brief Set the State Position object
     * 
     * @param param_r2 ...
     */
    void SetStatePosition2(GLfloat param_r2);

    /**
     * @brief Set the State Linear Speed object
     * 
     * @param param_v1 ...
     */
    void SetStateLinearSpeed1(GLfloat param_v1);

    /**
     * @brief Set the State Linear Speed object
     * 
     * @param param_v2 ...
     */
    void SetStateLinearSpeed2(GLfloat param_v2);

    /**
     * @brief Set the State Phi object
     * 
     * @param param_phi ...
     */
    void SetStatePhi(GLfloat param_phi);

    /**
     * @brief Set the State Angular Velocity object
     * 
     * @param param_omega ...
     */
    void SetStateAngularVelocity(GLfloat param_omega);

    /**
     * @brief Set the Command object
     * 
     * @param param_command ...
     */
    void SetCommand(std::vector<GLfloat> param_command);

    /**
     * @brief Set the Delta Time object
     * 
     * @param param_delta_time ...
     */
    void SetDeltaTime(GLfloat param_delta_time);

    /*Get-----------------------------------------*/

    /**
     * @brief Get the State Motor Speed object
     * 
     * @return GLfloat ...
     */
    GLfloat GetStateMotorSpeed1();

    /**
     * @brief Get the State Motor Speed object
     * 
     * @return GLfloat ...
     */
    GLfloat GetStateMotorSpeed2();

    /**
     * @brief Get the State Position object
     * 
     * @return GLfloat ...
     */
    GLfloat GetStatePosition1();

    /**
     * @brief Get the State Position object
     * 
     * @return GLfloat ...
     */
    GLfloat GetStatePosition2();

    /**
     * @brief Get the State Linear Speed object
     * 
     * @return <GLfloat ...
     */
    GLfloat GetStateLinearSpeed1();

    /**
     * @brief Get the State Linear Speed object
     * 
     * @return <GLfloat ...
     */
    GLfloat GetStateLinearSpeed2();

    /**
     * @brief Get the State Phi object
     * 
     * @return GLfloat ...
     */
    GLfloat GetStatePhi();
    
    /**
     * @brief Get the State Angular Velocity object
     * 
     * @return GLfloat ...
     */
    GLfloat GetStateAngularVelocity();

    /**
     * @brief Get the State Vector object
     * 
     * @return std::vector<GLfloat> ...
     */
    std::vector<GLfloat> GetStateVector();

    /**
     * @brief Get the Command object
     * 
     * @return std::vector<GLfloat> ...
     */
    std::vector<GLfloat> GetCommand();

    /**
     * @brief Get the Integration Step object
     * 
     * @return GLfloat ...
     */
    GLfloat GetIntegrationStep();

    /**
     * @brief Get the Delta Time object
     * 
     * @return GLfloat ...
     */
    GLfloat GetDeltaTime();

    struct DroneModelParameters
    {
        /** @brief  w_max | default (15000)*/
        GLfloat max_motor_speed;

        /** @brief  m | default (0.25) kg*/
        GLfloat mass;

        /** @brief  g | default (9.81) m/s^2*/
        GLfloat gravity_acc;

        /** @brief  l | default (0.1) m*/
        GLfloat wing_lenght;

        /** @brief  kf | default (1.744e-8)*/
        GLfloat force_constant;

        /** @brief  Iz | default (2e-4)*/
        GLfloat momentum_of_inercia;

        /** @brief  tau | default (0.005)*/
        GLfloat tau;

        /* Integration step */
        GLfloat integration_step;

        std::vector<GLfloat> state_vector;
        std::vector<GLfloat> command;
    };

private:
    /*--------------------------------------------*/

    DroneModelParameters m_drone_parameters;

    GLfloat m_delta_time;
    
};

#endif //_DRONE_MODEL_
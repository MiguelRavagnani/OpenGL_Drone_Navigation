#include "model.h"

#include <iostream>

#define PI 3.14159265f

Model::Model() : m_delta_time (0.0f)
{
    m_drone_parameters.state_vector.reserve(8);
    m_drone_parameters.state_vector = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    m_drone_parameters.command = {0.0f,0.0f};
}

Model::Model(
    GLfloat param_max_motor_speed,
    GLfloat param_mass,
    GLfloat param_gravity_acc,
    GLfloat param_wing_lenght,
    GLfloat param_force_constant,
    GLfloat param_momentum_of_inercia,
    GLfloat param_tau,
    GLfloat param_integration_step) : m_delta_time (0.0f)
{
    m_drone_parameters.max_motor_speed = param_max_motor_speed;
    m_drone_parameters.mass = param_mass;
    m_drone_parameters.gravity_acc = param_gravity_acc;
    m_drone_parameters.wing_lenght = param_wing_lenght;
    m_drone_parameters.force_constant = param_force_constant;
    m_drone_parameters.momentum_of_inercia = param_momentum_of_inercia;
    m_drone_parameters.tau = param_tau;
    m_drone_parameters.integration_step = param_integration_step;
    m_drone_parameters.state_vector = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    m_drone_parameters.command = {0.0f,0.0f};
}

std::vector<GLfloat> Model::StateVector(
    std::vector<GLfloat> param_time, 
    std::vector<GLfloat>* param_state_vector, 
    std::vector<GLfloat> param_input_cmd)
{
    /* Current states */

    glm::vec2 current_w = glm::vec2(
        (*param_state_vector)[0] * 60.0f * m_delta_time,
        (*param_state_vector)[1] * 60.0f * m_delta_time);

    glm::vec2 current_r = glm::vec2(
        (*param_state_vector)[2] * 60.0f * m_delta_time,
        (*param_state_vector)[3] * 60.0f * m_delta_time);

    glm::vec2 current_v = glm::vec2(
        (*param_state_vector)[4] * 60.0f * m_delta_time * -1.0f,
        (*param_state_vector)[5] * 60.0f * m_delta_time);

    glm::vec1 current_phi = glm::vec1((*param_state_vector)[6] * 60.0f * m_delta_time);

    glm::vec1 current_omega = glm::vec1((*param_state_vector)[7] * 60.0f * m_delta_time);

    /* Auxilay force 1 */
    glm::vec1 force_1 = glm::vec1(); 
    force_1[0] = m_drone_parameters.force_constant * current_w[0] * current_w[0] * 1.0f;
    
    /* Auxilay force 2 */
    glm::vec1 force_2 = glm::vec1(m_drone_parameters.force_constant * current_w[1] * current_w[1] * 1.0f);

    /* Torque */
    glm::vec1 torque = glm::vec1(m_drone_parameters.wing_lenght * (force_1[0] - force_2[0]));

    /* Control force */
    glm::vec2 control_force = glm::vec2(
        0.0f,
        force_1[0]*-3000.0f + force_2[0]*-3000.0f);

    /*  Rotation matrix */
    glm::mat2 rotation_matrix = glm::mat2(
        cos(current_phi[0]), -1.0f * sin(current_phi[0]),
        sin(current_phi[0]), cos(current_phi[0]));

    /* Derivatives */

    glm::vec2 w_dot = glm::vec2(
        ((-1.0f * current_w[0]) + param_input_cmd[0]) / m_drone_parameters.tau,
        ((-1.0f * current_w[1]) + param_input_cmd[1]) / m_drone_parameters.tau);

    glm::vec2 r_dot = current_v;
    glm::vec2 v_dot = ((rotation_matrix * control_force));
    v_dot.y = (1 / m_drone_parameters.mass) * (v_dot.y + (-1.0f * m_drone_parameters.mass * m_drone_parameters.gravity_acc));
    v_dot.x = (1 / m_drone_parameters.mass) * v_dot.x;
    glm::vec1 phi_dot = current_omega;
    glm::vec1 omega_dot = glm::vec1(torque / m_drone_parameters.momentum_of_inercia);

    m_drone_parameters.state_vector[0] = w_dot[0];
    m_drone_parameters.state_vector[1] = w_dot[1];
    m_drone_parameters.state_vector[2] = r_dot[0];
    m_drone_parameters.state_vector[3] = r_dot[1];
    m_drone_parameters.state_vector[4] = v_dot[0];
    m_drone_parameters.state_vector[5] = v_dot[1];
    m_drone_parameters.state_vector[6] = phi_dot[0];
    m_drone_parameters.state_vector[7] = omega_dot[0];

    return m_drone_parameters.state_vector;
}

Model::~Model() {}

void Model::UpdatePhysics()
{

}

void Model::Drone_SetGravity(GLfloat param_gravity)
{
    m_drone_parameters.gravity_acc = param_gravity;
}

GLfloat Model::Drone_GetGravity()
{
    return m_drone_parameters.gravity_acc;
}

void Model::Drone_SetStateMotorSpeed1(GLfloat param_w1)
{
    m_drone_parameters.state_vector[0] = param_w1;
}

void Model::Drone_SetStateMotorSpeed2(GLfloat param_w2)
{
    m_drone_parameters.state_vector[1] = param_w2;
}

void Model::Drone_SetStatePosition1(GLfloat param_r1)
{
    m_drone_parameters.state_vector[2] = param_r1;
}

void Model::Drone_SetStatePosition2(GLfloat param_r2)
{
    m_drone_parameters.state_vector[3] = param_r2;
}

void Model::Drone_SetStateLinearSpeed1(GLfloat param_v1)
{
    m_drone_parameters.state_vector[4] = param_v1;
}

void Model::Drone_SetStateLinearSpeed2(GLfloat param_v2)
{
    m_drone_parameters.state_vector[5] = param_v2;
}

void Model::Drone_SetStatePhi(GLfloat param_phi)
{
    m_drone_parameters.state_vector[6] = param_phi;
}

void Model::Drone_SetStateAngularVelocity(GLfloat param_omega)
{
    m_drone_parameters.state_vector[7] = param_omega;
}

void Model::Drone_SetCommand(std::vector<GLfloat> param_command)
{
    m_drone_parameters.command = param_command;
}

void Model::SetDeltaTime(GLfloat param_delta_time)
{
    m_delta_time = param_delta_time;
}

GLfloat Model::Drone_GetStateMotorSpeed1()
{
    return m_drone_parameters.state_vector[0];
}

GLfloat Model::Drone_GetStateMotorSpeed2()
{
    return m_drone_parameters.state_vector[1];
}

GLfloat Model::Drone_GetStatePosition1()
{
    return m_drone_parameters.state_vector[2];
}

GLfloat Model::Drone_GetStatePosition2()
{
    return m_drone_parameters.state_vector[3];
}

GLfloat Model::Drone_GetStateLinearSpeed1()
{
    return m_drone_parameters.state_vector[4];
}

GLfloat Model::Drone_GetStateLinearSpeed2()
{
    return m_drone_parameters.state_vector[5];
}

GLfloat Model::Drone_GetStatePhi()
{
    return m_drone_parameters.state_vector[6];
}

GLfloat Model::Drone_GetStateAngularVelocity()
{
    return m_drone_parameters.state_vector[7];
}

std::vector<GLfloat> Model::Drone_GetStateVector()
{
    return m_drone_parameters.state_vector;
}

GLfloat Model::Drone_GetIntegrationStep()
{
    return m_drone_parameters.integration_step;
}

std::vector<GLfloat> Model::Drone_GetCommand()
{
    return m_drone_parameters.command;
}

GLfloat Model::GetDeltaTime()
{
    return m_delta_time;
}

void Model::Control_SetWaypoint(glm::vec2 param_waypoint)
{
    m_control_parameters.waypoint = param_waypoint;
}

void Model::Control_SetError(glm::vec2 param_error)
{
    m_control_parameters.error = param_error;
}

glm::vec2 Model::Control_GetWaypoint()
{
    return m_control_parameters.waypoint;
}

glm::vec2 Model::Control_GetError()
{
    return m_control_parameters.error;
}

void Model::Control_CalculateError()
{
    m_control_parameters.error.x = m_control_parameters.waypoint.x - this->Drone_GetStatePosition1();
    m_control_parameters.error.y = m_control_parameters.waypoint.y - this->Drone_GetStatePosition2();

    // std::cout << "Error: (" << m_control_parameters.error.x << ", " << m_control_parameters.error.y << ")" << std::endl;
    // std::cout << "Mouse: (" << m_control_parameters.waypoint.x << ", " << m_control_parameters.waypoint.y << ")" << std::endl;
}
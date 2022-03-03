#include "model.h"

#include <iostream>

#define PI 3.14159265f

Model::Model() : m_delta_time (0.0f), m_controlled (false)
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
    GLfloat param_integration_step,
    GLfloat param_scale) : m_delta_time (0.0f), m_controlled (false)
{
    m_drone_parameters.scale = param_scale;
    m_drone_parameters.max_motor_speed = param_max_motor_speed;
    m_drone_parameters.mass = param_mass * pow(param_scale, 2);
    m_drone_parameters.gravity_acc = param_gravity_acc * -1.0f * param_scale;
    m_drone_parameters.wing_lenght = param_wing_lenght / param_scale;
    m_drone_parameters.force_constant = param_force_constant * param_scale;
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
        (*param_state_vector)[0],
        (*param_state_vector)[1]);

    glm::vec2 current_r = glm::vec2(
        (*param_state_vector)[2],
        (*param_state_vector)[3]);

    glm::vec2 current_v = glm::vec2(
        (*param_state_vector)[4] * -1.0f,
        (*param_state_vector)[5]);

    glm::vec1 current_phi = glm::vec1((*param_state_vector)[6]);

    glm::vec1 current_omega = glm::vec1((*param_state_vector)[7]);

    /* Auxilay force 1 */
    glm::vec1 force_1 = glm::vec1(m_drone_parameters.force_constant * pow(current_w[0], 2));
    
    /* Auxilay force 2 */
    glm::vec1 force_2 = glm::vec1(m_drone_parameters.force_constant * pow(current_w[1], 2));

    /* Torque */
    glm::vec1 torque = glm::vec1((m_drone_parameters.wing_lenght * (force_1[0] - force_2[0])));

    /* Control force */
    glm::vec2 control_force = glm::vec2(
        0.0f,
        (force_1[0] * - pow(m_drone_parameters.scale, 2)) + (force_2[0] * - pow(m_drone_parameters.scale, 2)));

    /*  Rotation matrix */
    glm::mat2 rotation_matrix = glm::mat2(
        cos(current_phi[0]), -1.0f * sin(current_phi[0]),
        sin(current_phi[0]), cos(current_phi[0]));

    /* Derivatives */

    glm::vec2 w_dot = glm::vec2(
        ((-1.0f * current_w[0]) + param_input_cmd[0]) / m_drone_parameters.tau,
        ((-1.0f * current_w[1]) + param_input_cmd[1]) / m_drone_parameters.tau);

    glm::vec2 r_dot = current_v;
    glm::vec2 v_dot = rotation_matrix * control_force;
    v_dot.y = (1 / m_drone_parameters.mass) * (v_dot.y + (-1.0f * m_drone_parameters.mass * m_drone_parameters.gravity_acc));
    v_dot.x = (1 / m_drone_parameters.mass) * v_dot.x;
    glm::vec1 phi_dot = current_omega;
    glm::vec1 omega_dot = glm::vec1(torque/ m_drone_parameters.momentum_of_inercia);

    m_drone_parameters.state_vector[0] = w_dot[0];
    m_drone_parameters.state_vector[1] = w_dot[1];
    m_drone_parameters.state_vector[2] = r_dot[0];
    m_drone_parameters.state_vector[3] = r_dot[1];
    m_drone_parameters.state_vector[4] = v_dot[0] * 5.0f * m_delta_time;
    m_drone_parameters.state_vector[5] = v_dot[1] * 5.0f * m_delta_time;
    m_drone_parameters.state_vector[6] = phi_dot[0];
    m_drone_parameters.state_vector[7] = omega_dot[0] * 5.0f *  m_delta_time ;

    return m_drone_parameters.state_vector;
}

std::vector<GLfloat> Model::Control_System(
    std::vector<GLfloat> param_state_vector)
{
    /* Control restrictions */

    float gravity_force = -1.0f * m_drone_parameters.mass * m_drone_parameters.gravity_acc;

    float phi_max = 15.0f * M_PI / 180.0f;

    float w_max = 15000.0f;

    float max_control_force = m_drone_parameters.force_constant / m_drone_parameters.scale * pow(w_max, 2);

    float max_torque = m_drone_parameters.wing_lenght * m_drone_parameters.force_constant / m_drone_parameters.scale * pow(w_max, 2);

    /* Current states */

    glm::vec2 current_w = glm::vec2(
        (param_state_vector)[0],
        (param_state_vector)[1]);

    glm::vec2 current_r = glm::vec2(
        (param_state_vector)[2],
        (param_state_vector)[3]);

    glm::vec2 current_v = glm::vec2(
        (param_state_vector)[4] * -1.0f,
        (param_state_vector)[5]);

    glm::vec1 current_phi = glm::vec1((param_state_vector)[6]);

    glm::vec1 current_omega = glm::vec1((param_state_vector)[7]);

    /* Position control */
    glm::vec1 kp_p(0.075f * 1.0f); 
    glm::vec1 kd_p(0.25f  * 1.0f); 
    
    Control_CalculatePositionError();
    glm::vec2 position_error = Control_GetPositionError();
    std::cout << "Position error: " << position_error.x << " " << position_error.y << " " << current_v.x << " " << current_v.y << std::endl;
    
    glm::vec2 position_command(0.0f, 0.0f);

    glm::vec2 velocity_error(position_command - current_v);

    float control_action_force_x = kp_p[0] * position_error[0] + kd_p[0] * velocity_error[0];
    float control_action_force_y = kp_p[0] * position_error[1] + kd_p[0] * velocity_error[1] - (gravity_force / pow(m_drone_parameters.scale, 3));

    control_action_force_y = std::min(-0.05f * max_control_force, std::max(control_action_force_y, -0.8f * (float)max_control_force));

    /* Attitude control */
    float phi_control_action = 1.0f * atan2(1.0f * control_action_force_x, 1.0f * control_action_force_y);

    std::cout << "Phi control action: " << phi_control_action << " | " << phi_max << std::endl;

    std::cout << "X before: " << control_action_force_x << std::endl;

    if (std::abs(phi_control_action) > phi_max)
    {
        float signal = phi_control_action / std::abs(phi_control_action);
        phi_control_action = -1.0f * signal * phi_max;
        control_action_force_x =  control_action_force_y * tan(phi_control_action);
    }

    std::cout << "X after: " << control_action_force_x << std::endl;

    glm::vec2 control_action_force_xy(control_action_force_x, control_action_force_y);

    float norm = 0.0f;

    norm = glm::length(control_action_force_xy);

    std::cout << "norm:" << norm << " x:" << control_action_force_x << " y:" << control_action_force_y << std::endl;

    glm::vec2 control_action_force_1_2(norm * m_drone_parameters.scale / 2.0f);

    /* Attitude constants */
    float kp_a = 0.75f * 0.01f; 
    float kd_a = 0.05f * 0.01f;

    float phi_error = (phi_control_action - current_phi[0]) * 10.0f;

    float omega_error = (0.0f - current_omega[0]) * 10.0f;

    float control_action_torque = 0.0f;

    if (omega_error != 0.0f)
    {
        control_action_torque = kp_a * phi_error * kd_a * omega_error;
    }
    else
    {
        control_action_torque = kp_a * phi_error * kd_a;
    }

    std::cout << " | " << kp_a << " | " <<  phi_error << " | " <<  kd_a << " | " <<  omega_error << std::endl;

    control_action_torque = std::max(-1.0f * (float)max_torque, std::min(control_action_torque, 1.0f * (float)max_torque));

    /* Forces delta */

    float delta_1_2 = std::abs(control_action_torque * 100000.0f);

    std::cout << "Action 1 2: " << control_action_force_1_2[0] << " " << control_action_force_1_2[1] << " Delta: " << delta_1_2 << std::endl;

    std::cout << control_action_torque << std::endl;

    if (control_action_torque >= 0.0f)
    {
        (control_action_force_1_2[0] = control_action_force_1_2[0] - delta_1_2);// *  position_error.x / 300.0f; 
        (control_action_force_1_2[1] = control_action_force_1_2[1] + delta_1_2);// * - 300.0f / position_error.x;
    }
    else
    {
        control_action_force_1_2[0] = control_action_force_1_2[0] + delta_1_2;// *  300.0f / position_error.x; 
        control_action_force_1_2[1] = control_action_force_1_2[1] - delta_1_2;// * position_error.x / 300.0f;
    }

    float w_1 = sqrt(control_action_force_1_2[0] * 1000.0f / (m_drone_parameters.force_constant * m_drone_parameters.scale));
    float w_2 = sqrt(control_action_force_1_2[1] * 1000.0f / (m_drone_parameters.force_constant * m_drone_parameters.scale));
    
    float w_1_out = std::max(0.0f, std::min(w_1, w_max));
    float w_2_out = std::max(0.0f, std::min(w_2, w_max));

    // float w_1_out = w_1;
    // float w_2_out = w_2;

    std::vector<GLfloat> w_output_action {w_1_out, w_2_out};

    return w_output_action;
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

void Model::Control_SetPositionError(glm::vec2 param_error)
{
    m_control_parameters.error = param_error;
}

glm::vec2 Model::Control_GetWaypoint()
{
    return m_control_parameters.waypoint;
}

glm::vec2 Model::Control_GetPositionError()
{
    return m_control_parameters.error;
}

void Model::Control_CalculatePositionError()
{
    m_control_parameters.error.x = m_control_parameters.waypoint.x - this->Drone_GetStatePosition1();
    m_control_parameters.error.y = m_control_parameters.waypoint.y - this->Drone_GetStatePosition2();

    // std::cout << "Error: (" << m_control_parameters.error.x << ", " << m_control_parameters.error.y << ")" << std::endl;
    // std::cout << "Mouse: (" << m_control_parameters.waypoint.x << ", " << m_control_parameters.waypoint.y << ")" << std::endl;
}

void Model::SetControlled(bool param_state)
{
    m_controlled = param_state;
}

bool Model::GetControlled()
{
    return m_controlled;
}

void Model::SetScale(GLfloat param_scale)
{
    m_drone_parameters.scale = param_scale;
}

GLfloat Model::GetScale()
{
    return m_drone_parameters.scale;
}

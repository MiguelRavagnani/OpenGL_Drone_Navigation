#include "model.h"

Model::Model()
{
    m_drone_parameters.state_vector.reserve(8);
}

Model::Model(
    GLfloat param_max_motor_speed,
    GLfloat param_mass,
    GLfloat param_gravity_acc,
    GLfloat param_wing_lenght,
    GLfloat param_force_constant,
    GLfloat param_momentum_of_inercia,
    GLfloat param_tau,
    GLfloat param_integration_step)
{
    m_drone_parameters.max_motor_speed = param_max_motor_speed;
    m_drone_parameters.mass = param_mass;
    m_drone_parameters.gravity_acc = param_gravity_acc;
    m_drone_parameters.wing_lenght = param_wing_lenght;
    m_drone_parameters.force_constant = param_force_constant;
    m_drone_parameters.momentum_of_inercia = param_momentum_of_inercia;
    m_drone_parameters.tau = param_tau;
    m_drone_parameters.integration_step = param_integration_step;
    m_drone_parameters.state_vector.reserve(8);
}

std::vector<GLfloat> Model::StateVector(
    std::vector<GLfloat> param_time, 
    std::vector<GLfloat> param_state_vector, 
    std::vector<GLfloat> param_input_cmd)
{
    /* Current states */
    
    glm::vec2 current_w = glm::vec2(
        param_state_vector[0],
        param_state_vector[1]);

    glm::vec2 current_r = glm::vec2(
        param_state_vector[2],
        param_state_vector[3]);

    glm::vec2 current_v = glm::vec2(
        param_state_vector[4],
        param_state_vector[5]);

    glm::vec1 current_phi = glm::vec1(param_state_vector[6]);

    glm::vec1 current_omega = glm::vec1(param_state_vector[7]);

    /* Auxilay force 1 */
    glm::vec1 force_1 = glm::vec1(); 
    force_1[0] = m_drone_parameters.force_constant * current_w[0]*current_w[0];
    
    /* Auxilay force 2 */
    glm::vec1 force_2 = glm::vec1(m_drone_parameters.force_constant * current_w[1]*current_w[1]);

    /* Torque */
    glm::vec1 torque = glm::vec1(1 * (force_1[0] - force_2[0]));

    /* Control force */
    glm::vec2 control_force = glm::vec2(
        0.0f,
        force_1[0] - force_2[0]);

    /*  Rotation matrix */
    glm::mat2 rotation_matrix = glm::mat2(
        cos(current_phi[0]), -1.0f * sin(current_phi[0]),
        sin(current_phi[0]), cos(current_phi[0]));

    /* Derivatives */

    glm::vec2 w_dot = glm::vec2(
        ((-1.0f * current_w[0]) + param_input_cmd[0]) / m_drone_parameters.tau,
        ((-1.0f * current_w[1]) + param_input_cmd[1]) / m_drone_parameters.tau);

    glm::vec2 r_dot = current_v;
    glm::vec2 v_dot = (1 / m_drone_parameters.mass) * ((rotation_matrix * control_force) + (-1.0f * m_drone_parameters.mass * m_drone_parameters.gravity_acc));
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

void Model::SetStateMotorSpeed1(GLfloat param_w1)
{
    m_drone_parameters.state_vector[0] = param_w1;
}

void Model::SetStateMotorSpeed2(GLfloat param_w2)
{
    m_drone_parameters.state_vector[1] = param_w2;
}

void Model::SetStatePosition1(GLfloat param_r1)
{
    m_drone_parameters.state_vector[2] = param_r1;
}

void Model::SetStatePosition2(GLfloat param_r2)
{
    m_drone_parameters.state_vector[3] = param_r2;
}

void Model::SetStateLinearSpeed1(GLfloat param_v1)
{
    m_drone_parameters.state_vector[4] = param_v1;
}

void Model::SetStateLinearSpeed2(GLfloat param_v2)
{
    m_drone_parameters.state_vector[5] = param_v2;
}

void Model::SetStatePhi(GLfloat param_phi)
{
    m_drone_parameters.state_vector[6] = param_phi;
}

void Model::SetStateAngularVelocity(GLfloat param_omega)
{
    m_drone_parameters.state_vector[7] = param_omega;
}

void Model::SetCommand(std::vector<GLfloat> param_command)
{
    m_drone_parameters.command = param_command;
}

GLfloat Model::GetStateMotorSpeed1()
{
    return m_drone_parameters.state_vector[0];
}

GLfloat Model::GetStateMotorSpeed1()
{
    return m_drone_parameters.state_vector[1];
}

GLfloat Model::GetStatePosition1()
{
    return m_drone_parameters.state_vector[2];
}

GLfloat Model::GetStatePosition2()
{
    return m_drone_parameters.state_vector[3];
}

GLfloat Model::GetStateLinearSpeed1()
{
    return m_drone_parameters.state_vector[4];
}

GLfloat Model::GetStateLinearSpeed2()
{
    return m_drone_parameters.state_vector[5];
}

GLfloat Model::GetStatePhi()
{
    return m_drone_parameters.state_vector[6];
}

GLfloat Model::GetStateAngularVelocity()
{
    return m_drone_parameters.state_vector[7];
}

std::vector<GLfloat> Model::GetStateVector()
{
    return m_drone_parameters.state_vector;
}

GLfloat Model::GetIntegrationStep()
{
    return m_drone_parameters.integration_step;
}
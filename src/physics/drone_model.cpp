#include "drone_model.h"

DroneModel::DroneModel()

    : m_max_motor_speed (15000.0f),
      m_mass (0.25f),
      m_gravity_acc (9.81f),
      m_wing_lenght (0.1f),
      m_force_constant (0.00000001744f),
      m_momentum_of_inercia (0.0002), 
      m_tau (0.005f),
      m_integration_step ()
{
    m_state_vector.reserve(8);
}

DroneModel::DroneModel(
    GLfloat param_max_motor_speed,
    GLfloat param_mass,
    GLfloat param_gravity_acc,
    GLfloat param_wing_lenght,
    GLfloat param_force_constant,
    GLfloat param_momentum_of_inercia,
    GLfloat param_tau,
    GLfloat param_integration_step)
    
    : m_max_motor_speed (param_max_motor_speed),
      m_mass (param_mass),
      m_gravity_acc (param_gravity_acc),
      m_wing_lenght (param_wing_lenght),
      m_force_constant (param_force_constant),
      m_momentum_of_inercia (param_momentum_of_inercia), 
      m_tau (param_tau),
      m_integration_step (param_integration_step)
{
    m_state_vector.reserve(8);
}

std::vector<GLfloat> DroneModel::StateVectorModel(
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
    force_1[0] = m_force_constant * current_w[0]*current_w[0];
    
    /* Auxilay force 2 */
    glm::vec1 force_2 = glm::vec1(m_force_constant * current_w[1]*current_w[1]);

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
        ((-1.0f * current_w[0]) + param_input_cmd[0]) / m_tau,
        ((-1.0f * current_w[1]) + param_input_cmd[1]) / m_tau);

    glm::vec2 r_dot = current_v;
    glm::vec2 v_dot = (1 / m_mass) * ((rotation_matrix * control_force) + (-1.0f * m_mass * m_gravity_acc));
    glm::vec1 phi_dot = current_omega;
    glm::vec1 omega_dot = glm::vec1(torque / m_momentum_of_inercia);

    m_state_vector[0] = w_dot[0];
    m_state_vector[1] = w_dot[1];
    m_state_vector[2] = r_dot[0];
    m_state_vector[3] = r_dot[1];
    m_state_vector[4] = v_dot[0];
    m_state_vector[5] = v_dot[1];
    m_state_vector[6] = phi_dot[0];
    m_state_vector[7] = omega_dot[0];

    return m_state_vector;
}

DroneModel::~DroneModel() {}
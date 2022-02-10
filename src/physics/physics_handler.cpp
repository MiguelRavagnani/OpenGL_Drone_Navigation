#include "physics_handler.h"

void Physics::FourthOrder::UpdatePhysics(Model* param_drone_model)
{
    std::vector<GLfloat> time {0.0f};
    std::vector<GLfloat> integration_step {param_drone_model->GetIntegrationStep()};
    std::vector<GLfloat> calc_state_vector;

    calc_state_vector = Math::FourthOrder::RungeKutta(
        time,
        integration_step,
        param_drone_model->GetStateVector(),
        param_drone_model->GetCommand(),
        param_drone_model);

    param_drone_model->SetStateMotorSpeed1(calc_state_vector[0]);
    param_drone_model->SetStateMotorSpeed2(calc_state_vector[1]);
    param_drone_model->SetStatePosition1(calc_state_vector[2]);
    param_drone_model->SetStatePosition2(calc_state_vector[3]);
    param_drone_model->SetStateLinearSpeed1(calc_state_vector[4]);
    param_drone_model->SetStateLinearSpeed2(calc_state_vector[5]);
    param_drone_model->SetStatePhi(calc_state_vector[6]);
    param_drone_model->SetStateAngularVelocity(calc_state_vector[7]);
}
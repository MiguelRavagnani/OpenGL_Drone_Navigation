#include "physics_handler.h"

#include <iostream>

void Physics::FourthOrder::UpdatePhysics(Model* param_drone_model)
{
    std::vector<GLfloat> time {0.0f};
    std::vector<GLfloat> integration_step {param_drone_model->Drone_GetIntegrationStep()};
    std::vector<GLfloat> calc_state_vector;

    calc_state_vector = Math::FourthOrder::RungeKutta(
        time,
        integration_step,
        param_drone_model->Drone_GetStateVector(),
        param_drone_model->Drone_GetCommand(),
        param_drone_model);

    param_drone_model->Drone_SetStateMotorSpeed1(calc_state_vector[0]);
    param_drone_model->Drone_SetStateMotorSpeed2(calc_state_vector[1]);
    param_drone_model->Drone_SetStatePosition1(calc_state_vector[2]);
    param_drone_model->Drone_SetStatePosition2(calc_state_vector[3]);
    param_drone_model->Drone_SetStateLinearSpeed1(calc_state_vector[4]);
    param_drone_model->Drone_SetStateLinearSpeed2(calc_state_vector[5]);
    param_drone_model->Drone_SetStatePhi(calc_state_vector[6]);
    param_drone_model->Drone_SetStateAngularVelocity(calc_state_vector[7]);
}
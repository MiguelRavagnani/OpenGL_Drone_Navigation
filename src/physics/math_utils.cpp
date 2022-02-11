#include "math_utils.h"

#include <iostream>

std::vector<GLfloat> Math::FourthOrder::RungeKutta(
    std::vector<GLfloat> param_current_time,
    std::vector<GLfloat> param_integration_step,
    std::vector<GLfloat> param_current_state_vector,
    std::vector<GLfloat> param_current_input_cmd,
    Model* param_model)
{
    std::vector<GLfloat> k_time;
    k_time.push_back(param_current_time[0] + param_integration_step[0] / 2.0f);

    std::vector<GLfloat> k_1 = param_model->StateVector(
        param_current_time, 
        &param_current_state_vector, 
        param_current_input_cmd);
    
    std::vector<GLfloat> k_input 
    {
        param_current_state_vector[0] + (k_1[0] * param_integration_step[0] / 2.0f),
        param_current_state_vector[1] + (k_1[1] * param_integration_step[0] / 2.0f),
        param_current_state_vector[2] + (k_1[2] * param_integration_step[0] / 2.0f),
        param_current_state_vector[3] + (k_1[3] * param_integration_step[0] / 2.0f),
        param_current_state_vector[4] + (k_1[4] * param_integration_step[0] / 2.0f),
        param_current_state_vector[5] + (k_1[5] * param_integration_step[0] / 2.0f),
        param_current_state_vector[6] + (k_1[6] * param_integration_step[0] / 2.0f),
        param_current_state_vector[7] + (k_1[7] * param_integration_step[0] / 2.0f)
    };

    std::vector<GLfloat> k_2 = param_model->StateVector(
        k_time, 
        &k_input, 
        param_current_input_cmd);

    k_input[0] = param_current_state_vector[0] + (k_2[0] * param_integration_step[0] / 2.0f);
    k_input[1] = param_current_state_vector[1] + (k_2[1] * param_integration_step[0] / 2.0f);
    k_input[2] = param_current_state_vector[2] + (k_2[2] * param_integration_step[0] / 2.0f);
    k_input[3] = param_current_state_vector[3] + (k_2[3] * param_integration_step[0] / 2.0f);
    k_input[4] = param_current_state_vector[4] + (k_2[4] * param_integration_step[0] / 2.0f);
    k_input[5] = param_current_state_vector[5] + (k_2[5] * param_integration_step[0] / 2.0f);
    k_input[6] = param_current_state_vector[6] + (k_2[6] * param_integration_step[0] / 2.0f);
    k_input[7] = param_current_state_vector[7] + (k_2[7] * param_integration_step[0] / 2.0f);

    std::vector<GLfloat> k_3 = param_model->StateVector(
        k_time, 
        &k_input,
        param_current_input_cmd);

    k_time[0] = k_time[0] * 2.0f;

    k_input[0] = param_current_state_vector[0] + (k_3[0] * param_integration_step[0]);
    k_input[1] = param_current_state_vector[1] + (k_3[1] * param_integration_step[0]);
    k_input[2] = param_current_state_vector[2] + (k_3[2] * param_integration_step[0]);
    k_input[3] = param_current_state_vector[3] + (k_3[3] * param_integration_step[0]);
    k_input[4] = param_current_state_vector[4] + (k_3[4] * param_integration_step[0]);
    k_input[5] = param_current_state_vector[5] + (k_3[5] * param_integration_step[0]);
    k_input[6] = param_current_state_vector[6] + (k_3[6] * param_integration_step[0]);
    k_input[7] = param_current_state_vector[7] + (k_3[7] * param_integration_step[0]);

    std::vector<GLfloat> k_4 = param_model->StateVector(
        k_time, 
        &k_input, 
        param_current_input_cmd);

    std::vector<GLfloat> k_output
    {
        param_current_state_vector[0] + (param_integration_step[0] / 6.0f) * (k_1[0] + k_2[0] * 2.0f + k_3[0] * 2.0f + k_4[0]),
        param_current_state_vector[1] + (param_integration_step[0] / 6.0f) * (k_1[1] + k_2[1] * 2.0f + k_3[1] * 2.0f + k_4[1]),
        param_current_state_vector[2] + (param_integration_step[0] / 6.0f) * (k_1[2] + k_2[2] * 2.0f + k_3[2] * 2.0f + k_4[2]),
        param_current_state_vector[3] + (param_integration_step[0] / 6.0f) * (k_1[3] + k_2[3] * 2.0f + k_3[3] * 2.0f + k_4[3]),
        param_current_state_vector[4] + (param_integration_step[0] / 6.0f) * (k_1[4] + k_2[4] * 2.0f + k_3[4] * 2.0f + k_4[4]),
        param_current_state_vector[5] + (param_integration_step[0] / 6.0f) * (k_1[5] + k_2[5] * 2.0f + k_3[5] * 2.0f + k_4[5]),
        param_current_state_vector[6] + (param_integration_step[0] / 6.0f) * (k_1[6] + k_2[6] * 2.0f + k_3[6] * 2.0f + k_4[6]),
        param_current_state_vector[7] + (param_integration_step[0] / 6.0f) * (k_1[7] + k_2[7] * 2.0f + k_3[7] * 2.0f + k_4[7])
    };

    return k_output;
}

GLfloat Math::Conversion::RadiansToDegrees(GLfloat param_radians)
{
    return param_radians * 180.0f / PI;
}

GLfloat Math::Conversion::DegreesToRadians(GLfloat param_degrees)
{
    return param_degrees * PI / 180.0f;
}
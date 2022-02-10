#ifndef _PHYSICS_HANDLER_
#define _PHYSICS_HANDLER_

/** 
 *  @file   physics_handler.h 
 *  @brief  Library description
 *  @date   2022-08-02 
 **************************************************/

#include "math_utils.h"
#include "model.h"

/**
 * @brief Phyisics utility
 */
namespace Physics
{
    namespace FourthOrder
    {
        void UpdatePhysics(Model* param_drone_model);
    }
}

#endif //_PHYSICS_HANDLER_
 
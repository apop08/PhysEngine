#pragma once
#include "../../TypeDefs/Precision.h"
#include "../BaseTypes/Vector3.h"

/*
* Simple Physics object just a point in space with mass
*/
class Particle
{
protected:
    Vector3 Position;
    Vector3 Velocity;
    Vector3 Acceleration;

    /*
    * Fake drag
    */
    FLOAT Damping;

    /*
    * Inverse of Mass for easier integration
    * Will often have objects of large mass over objects of small mass
    */
    FLOAT InverseMass;

public:
    void Update(FLOAT deltaTime);
};
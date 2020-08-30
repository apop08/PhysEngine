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

    Vector3 ForceAccumulation;

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
    void AddForce(const Vector3& force);

    // Getters and Setters
    Vector3 GetPosition() const
    {
        return Position;
    }

    void SetPosition(const Vector3& vector)
    {
        Position = vector;
    }
    
    void SetPosition(const FLOAT& x, const FLOAT& y = 0.f, const FLOAT& z = 0.f)
    {
        Position.X = x;
        Position.Y = y;
        Position.Z = z;
    }

    Vector3 GetVelocity() const
    {
        return Velocity;
    }

    void SetVelocity(const Vector3& vector)
    {
        Velocity = vector;
    }
    
    void SetVelocity(const FLOAT& x, const FLOAT& y = 0.f, const FLOAT& z = 0.f)
    {
        Velocity.X = x;
        Velocity.Y = y;
        Velocity.Z = z;
    }

    Vector3 GetAcceleration() const
    {
        return Acceleration;
    }

    void SetAcceleration(const Vector3& vector)
    {
        Acceleration = vector;
    }

    void SetAcceleration(const FLOAT& x, const FLOAT& y = 0.f, const FLOAT& z = 0.f)
    {
        Acceleration.X = x;
        Acceleration.Y = y;
        Acceleration.Z = z;
    }

    FLOAT GetDamping() const
    {
        return Damping;
    }

    void SetDamping(const FLOAT& value)
    {
        Damping = value;
    }

    FLOAT GetMass() const
    {
        return 1.f / InverseMass;
    }

    void SetMass(const FLOAT& value)
    {
        InverseMass = 1.f / value;
    }

private:
    void ClearAccumulator();
};
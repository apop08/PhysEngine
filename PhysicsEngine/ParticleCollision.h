#pragma once
#include "Particle.h"

/*
* Contact is a collision between two objects contains no logic just physics
*/
class ParticleContact
{
public:
    Particle* Particle[2];
    FLOAT Restitution;
    Vector3 ContactNormal;
    FLOAT Penetration;
    Vector3 ParticleMovement[2];

protected:
    void Resolve(FLOAT deltaTime);
    FLOAT CalculateSeparatingVelocity() const;

private:
    void ResolveVelocity(FLOAT deltaTime);
    void ResolvePenetration(FLOAT deltaTime);
};
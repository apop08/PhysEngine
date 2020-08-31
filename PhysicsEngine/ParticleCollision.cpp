#include "ParticleCollision.h"

void ParticleContact::Resolve(FLOAT deltaTime)
{
    ResolveVelocity(deltaTime);
    ResolvePenetration(deltaTime);
}

FLOAT ParticleContact::CalculateSeparatingVelocity() const
{
    Vector3 relativeVelocity = (Particle[1]) ? Particle[0]->GetVelocity() - Particle[1]->GetVelocity() :
                                               Particle[0]->GetVelocity();

    return relativeVelocity * ContactNormal;
}

void ParticleContact::ResolveVelocity(FLOAT deltaTime)
{
    FLOAT separatingVelocity = CalculateSeparatingVelocity();

    if (separatingVelocity > 0)
    {
        return;
    }

    FLOAT newSepartionVelocity = -separatingVelocity * Restitution;
    FLOAT deltaVelocity = newSepartionVelocity - separatingVelocity;

    FLOAT totalInverseMass = (Particle[1]) ? Particle[0]->GetInverseMass() + Particle[1]->GetInverseMass() :
                                             Particle[0]->GetInverseMass();
    // All Particles have infinite mass do nothing
    if (totalInverseMass <= 0) return;

    FLOAT impulse = deltaVelocity / totalInverseMass;
    Vector3 impulsePerInverseMass = ContactNormal * impulse;

    Particle[0]->SetVelocity(Particle[0]->GetVelocity() + impulsePerInverseMass *
                             Particle[0]->GetInverseMass);

    if (Particle[1])
    {
        Particle[1]->SetVelocity(Particle[1]->GetVelocity() + impulsePerInverseMass *
            -Particle[1]->GetInverseMass);
    }
}

void ParticleContact::ResolvePenetration(FLOAT deltaTime)
{
    if (Penetration <= 0)
    {
        return;
    }

    FLOAT totalInverseMass = (Particle[1]) ? Particle[0]->GetInverseMass() + Particle[1]->GetInverseMass() :
        Particle[0]->GetInverseMass();
    // All Particles have infinite mass do nothing
    if (totalInverseMass <= 0) return;

    Vector3 distancePerIMass = ContactNormal * (Penetration / totalInverseMass);

    ParticleMovement[0] = distancePerIMass * Particle[0]->GetInverseMass();

    if (Particle[1])
    {
        ParticleMovement[1] = distancePerIMass * -Particle[0]->GetInverseMass();
    }
    else
    {
        ParticleMovement[1].Clear();
    }

    Particle[0]->SetPosition(Particle[0]->GetPosition() + ParticleMovement[0]);
    if (Particle[1])
    {
        Particle[1]->SetPosition(Particle[1]->GetPosition() + ParticleMovement[1]);
    }
}
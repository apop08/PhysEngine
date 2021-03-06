#include "PForces.h"

void ParticleForceMap::Add(Particle* particle, ParticleForce* force)
{
    ForceMaps.push_back(ParticleForceMapEntry{ particle, force });
}

void ParticleForceMap::Remove(Particle* particle, ParticleForce* force)
{
    ForceMap::iterator it = ForceMaps.begin();
    for (; it != ForceMaps.end(); it++)
    {
        if (it->Force == force && it->Particle == particle)
        {
            break;
        }
    }
    if (it != ForceMaps.end())
    {
        ForceMaps.erase(it);
    }
}

void ParticleForceMap::Clear()
{
    ForceMaps.clear();
}

void ParticleForceMap::UpdateForces(FLOAT deltaTime)
{
    for (ForceMap::iterator it = ForceMaps.begin(); it != ForceMaps.end(); it++)
    {
        it->Force->UpdateForce(it->Particle, deltaTime);
    }
}

void ParticleGravity::UpdateForce(Particle* particle, FLOAT deltaTime)
{
    if (!particle->HasFiniteMass())
        return;

    particle->AddForce(Gravity * particle->GetMass());
}

void ParticleDrag::UpdateForce(Particle* particle, FLOAT deltaTime)
{
    Vector3 force;
    particle->GetVelocity(&force);

    FLOAT dragCoef = force.Magnitude();
    dragCoef = K1 * dragCoef + K2 * dragCoef * dragCoef;

    force.Normalize();
    force *= -dragCoef;
    particle->AddForce(force);
}

void ParticleSpring::UpdateForce(Particle* particle, FLOAT deltaTime)
{
    Vector3 force;
    particle->GetPosition(&force);
    force -= Other->GetPosition();

    FLOAT magnitude = force.Magnitude();
    magnitude = FLOATAbs(magnitude - RestLength);
    magnitude *= SpringConstant;

    force.Normalize();
    force *= -magnitude;
    particle->AddForce(force);
}

void ParticleAnchoredSpring::UpdateForce(Particle* particle, FLOAT deltaTime)
{
    Vector3 force;
    particle->GetPosition(&force);
    force -= *Anchor;

    FLOAT magnitude = force.Magnitude();
    magnitude = (RestLength - magnitude) * SpringConstant;

    force.Normalize();
    force *= magnitude;
    particle->AddForce(force);
}

void ParticleBungee::UpdateForce(Particle* particle, FLOAT deltaTime)
{
    Vector3 force;
    particle->GetPosition(&force);
    force -= Other->GetPosition();

    FLOAT magnitude = force.Magnitude();
    if (magnitude <= RestLength) return;

    magnitude = SpringConstant * (RestLength - magnitude);

    force.Normalize();
    force *= -magnitude;
    particle->AddForce(force);
}

void ParticleBuoyancy::UpdateForce(Particle* particle, FLOAT deltaTime)
{
    FLOAT depth = particle->GetPosition().Y;

    if (depth >= WaterHeight + MaxDepth) return;

    Vector3 force(0, 0, 0);
    if (depth <= WaterHeight - MaxDepth)
    {
        force.Y = LiquidDensity * Volume;
        particle->AddForce(force);
        return;
    }

    force.Y = LiquidDensity * Volume * (depth - MaxDepth - WaterHeight) /
        2 * MaxDepth;
    particle->AddForce(force);
}
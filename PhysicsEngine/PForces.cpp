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
    particle->GetVelocity();
}

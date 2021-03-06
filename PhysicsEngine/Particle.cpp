#include "Particle.h"
#include "DebugEngine.h"

void Particle::Update(FLOAT deltaTime)
{
    // infinite mass does not move
    if (InverseMass <= 0.0f) return;

    // check frame time
    assert(deltaTime > 0.0);

    /* 
    * Does not follow v * dt + a * dt * dt / 2 as dt is tiny and idealy so should acceleration
    * High acceleration will be buggy
    */
    Position.AddScaledVector(Velocity, deltaTime);
    Vector3 resultingAcceleration = Acceleration;
    Velocity.AddScaledVector(resultingAcceleration, deltaTime);
    Velocity *= FLOATPow(Damping, deltaTime);

    // clears force accumulators
    ClearAccumulator();
}

void Particle::ClearAccumulator()
{
    ForceAccumulation.Clear();
}

void Particle::AddForce(const Vector3& force)
{
    ForceAccumulation += force;
}

bool Particle::HasFiniteMass() const
{
    return (InverseMass >= 0.0f);
}
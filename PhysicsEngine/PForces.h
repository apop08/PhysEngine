#pragma once
#include "Containers.h"
#include "Precision.h"
#include "Particle.h"

class ParticleForce
{
public:
    virtual void UpdateForce(const Particle* particle, const FLOAT& deltaTime) = 0;
};

/*
* maps particles and forces
*/
class ParticleForceMap
{
protected:
    struct ParticleForceMapEntry
    {
        Particle* Particle;
        ParticleForce* Force;
    };

    typedef vector<ParticleForceMapEntry> ForceMap;
    ForceMap ForceMaps;

public:
    void Add(Particle* particle, ParticleForce* force);
    void Remove(Particle* particle, ParticleForce* force);
    void Clear();
    void UpdateForces(FLOAT deltaTime);
};

class ParticleGravity : public ParticleForce
{
private:
    Vector3 Gravity;

public:
    ParticleGravity(const Vector3& gravity) : Gravity(gravity) {}
    virtual void UpdateForce(Particle* particle, FLOAT deltaTime);
};

// -v(k1 * v + k2 * v^2)
class ParticleDrag : public ParticleForce
{
private:
    FLOAT K1;
    FLOAT K2;

public:
    ParticleDrag(const FLOAT& k1, const FLOAT& k2) : K1(k1), K2(k2) {}
    virtual void UpdateForce(Particle* particle, FLOAT deltaTime);
};

/*
* Spring between two particles
*/
class ParticleSpring : public ParticleForce
{
private:
    Particle* Other;
    FLOAT SpringConstant;
    FLOAT RestLength;

public:
    ParticleSpring(Particle* other, const FLOAT& springConstant, const FLOAT& restLength) : 
                   Other(other),
                   SpringConstant(springConstant),
                   RestLength(restLength) {}
    virtual void UpdateForce(Particle* particle, FLOAT deltaTime);
};

/*
* Spring between particle and fixed point
*/
class ParticleAnchoredSpring : public ParticleForce
{
private:
    Vector3* Anchor;
    FLOAT SpringConstant;
    FLOAT RestLength;

public:
    ParticleAnchoredSpring(Vector3* anchor, const FLOAT& springConstant, const FLOAT& restLength) :
        Anchor(anchor),
        SpringConstant(springConstant),
        RestLength(restLength) {}
    virtual void UpdateForce(Particle* particle, FLOAT deltaTime);
};

class ParticleBungee : public ParticleForce
{
private:
    Particle* Other;
    FLOAT SpringConstant;
    FLOAT RestLength;

public:
    ParticleBungee(Particle* other, const FLOAT& springConstant, const FLOAT& restLength) :
        Other(other),
        SpringConstant(springConstant),
        RestLength(restLength) {}
    virtual void UpdateForce(Particle* particle, FLOAT deltaTime);
};

class ParticleBuoyancy : public ParticleForce
{
private:
    FLOAT MaxDepth;
    FLOAT Volume;
    FLOAT WaterHeight;
    FLOAT LiquidDensity;

public:
    ParticleBuoyancy(const FLOAT& maxDepth, const FLOAT& volume,
                     const FLOAT& waterHeight, const FLOAT& liquidDensity) :
        MaxDepth(maxDepth),
        Volume(volume),
        WaterHeight(waterHeight),
        LiquidDensity(liquidDensity) {}
    virtual void UpdateForce(Particle* particle, FLOAT deltaTime);
};
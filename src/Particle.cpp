#include "psocxx.hpp"


namespace psocxx {
    
Particle::Particle(void)
{

}


Particle::Particle(const Vector& position)
    : mVelocity(0)
{
    mPosition = new Vector(position);
    mBestPosition = new Vector(position);
}

Particle::Particle(const Vector& position, const Vector& velocity)
{
    mPosition = new Vector(position);
    mVelocity = new Vector(velocity);
    mBestPosition = new Vector(position);
}

Particle::Particle(const Particle& n)
{
    
}

Particle::~Particle(void)
{
    delete mPosition;
    delete mVelocity;
    delete mBestPosition;
}

const std::string Particle::ToString(void) const
{
    std::ostringstream oss;
    
    oss << "Particle: Position(" << mPosition->ToString() << ")";
    
    if (mVelocity!=0)
        oss << ", Velocity(" << mVelocity->ToString() << ")";
    
    if (mBestPosition!=0)
        oss << ", Best Position(" << mBestPosition->ToString() << ")";
    
    return oss.str();
}


}

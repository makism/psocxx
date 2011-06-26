#include "psocxx.hpp"


namespace psocxx {
    
Particle::Particle(const Vector& position)
    : mVelocity(0),
      mParent(0)
{
    mPosition = new Vector(position);
    mBestPosition = new Vector(position);
}

Particle::Particle(const Vector& position, const Vector& velocity)
    : mParent(0)
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

void Particle::Evaluate(void)
{
    float res = EvaluateCallback(mPosition);
    
    if (res < mParent->mBestFitness) {
        mParent->mBestFitness = res;
        mParent->mBestPosition = mPosition;
    }
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

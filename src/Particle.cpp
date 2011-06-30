#include "psocxx.hpp"


namespace psocxx {
    
Particle::Particle(const Vector& position)
    : mVelocity(0),
      mParent(0),
      mFitness(0.0f)
{
    mPosition = new Vector(position);
    mBestPosition = new Vector(position);
}

Particle::Particle(const Vector& position, const Vector& velocity)
    : mParent(0),
      mFitness(0.0f)
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

void Particle::Evaluate(bool step)
{
    float res = EvaluateCallback(mPosition);
    
    mFitness = res;
    
    if (step) {
        float res2 = EvaluateCallback(mBestPosition);
     
        if (res < res2) {
            delete mBestPosition;
            mBestPosition = new Vector(*mPosition);
            
            if (res2 < mParent->mBestFitness) {
                mParent->mBestFitness = res2;
                
                delete mParent->mBestPosition;
                mParent->mBestPosition = new Vector(*mBestPosition);
            }
        }
    } else {
        if (mParent->mBestPosition==0) {
            mParent->mBestFitness = res;
            
            delete mParent->mBestPosition;
            mParent->mBestPosition = new Vector(*mPosition);
            
            return;
        }
        
        if (res < mParent->mBestFitness) {
            mParent->mBestFitness = res;
            
            delete mParent->mBestPosition;
            mParent->mBestPosition = new Vector(*mPosition);
        }
    }
}

Vector* Particle::Position(void) const
{
    return mPosition;
}

void Particle::SetPosition(Vector* v)
{
    mPosition = v;
}

Vector* Particle::Velocity(void) const
{
    return mVelocity;
}

void Particle::SetVelocity(Vector* v)
{
    mVelocity = v;
}

Vector* Particle::BestPosition(void) const
{
    return mBestPosition;
}

float Particle::Fitness(void) const
{
    return mFitness;
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

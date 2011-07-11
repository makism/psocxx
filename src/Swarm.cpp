#include "psocxx.hpp"


namespace psocxx {

Swarm::Swarm(const int& numberOfParticles)
    : mNumberOfParticles(numberOfParticles),
      mBestPosition(0),
      mBoundaryLo(0.0f),
      mBoundaryHi(0.0f),
      mRand(0),
      mHasInited(false)
{
    mParticles = new std::vector<Particle*>();
}

Swarm::~Swarm(void)
{
    for (int i=0; i<mNumberOfParticles; i++)
        delete mParticles->at(i);
    
    mParticles->clear();
    delete mParticles;
    
    delete mBestPosition;
    delete mRand;
}

void Swarm::ConfigureSpace(const int& dims, const float& lo, const float& hi)
{
    mDimensions = dims;
    mBoundaryLo = lo;
    mBoundaryHi = hi;
    
    mRand = Helpers::Random::Instance(lo, hi);
}

void Swarm::SetParameters(const float& omega, const float& phi_p, const float& phi_g)
{
    mParamOmega = omega;
    mParamPhiP = phi_p;
    mParamPhiG = phi_g;
}

std::vector<Particle *>* Swarm::Particles(void) const
{
    return mParticles;
}

int Swarm::NumberOfParticles(void) const
{
    return mNumberOfParticles;
}

void Swarm::Init(void)
{
    for (int i=0; i<mNumberOfParticles; i++) {
        std::vector<float> points;
        std::vector<float> v_points;
        
        for (int x=0; x<mDimensions; x++) {
            points.push_back(mRand->Position());
            v_points.push_back(mRand->Velocity());
        }
        
        Vector position(points);
        Vector velocity(v_points);
        Particle* p = new Particle(position, velocity);
        p->mParent = this;
        p->Evaluate();
        
        mParticles->push_back(p);
    }
    
    mHasInited = true;
}

bool Swarm::HasInited(void) const
{
    return mHasInited;
}

Vector* Swarm::BestPosition(void) const
{
    return mBestPosition;
}

void Swarm::Step(void)
{
    for (int i=0; i<mNumberOfParticles;i ++) {
        float Rp = mRand->UniformUnit();
        float Rg = mRand->UniformUnit();
        
        Vector* pos = mParticles->at(i)->Position();
        Vector* bpos = mParticles->at(i)->BestPosition();
        Vector* vel = mParticles->at(i)->Velocity();
        
        // Update velocity.
        (*vel) *= mParamOmega;
        
        Vector* temp = new Vector(*bpos);
        (*temp) -= (*pos);
        (*temp) *= mParamPhiP * Rp;
        (*vel) += (*temp);
        
        Vector* temp2 = new Vector(*mBestPosition);
        (*temp2) -= (*pos);
        (*temp2) *= mParamPhiG * Rg;
        (*vel) += (*temp2);
    
        // Update position.
        (*pos) += (*vel);
        
        // Evaluate particle.
        mParticles->at(i)->Evaluate(true);
    
        delete temp;
        delete temp2;
   }
}

}

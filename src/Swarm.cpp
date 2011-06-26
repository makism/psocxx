#include "psocxx.hpp"


namespace psocxx {

Swarm::Swarm(const int& numberOfParticles)
    : mNumberOfParticles(numberOfParticles),
      mBestPosition(0),
      mBoundaryLo(0.0f),
      mBoundaryHi(0.0f),
      mRand(0)
{
    mParticles = new std::vector<Particle*>();
}

Swarm::~Swarm(void)
{
    for (int i=0; i<mNumberOfParticles; i++)
        delete mParticles->at(i);
    
    mParticles->clear();
    delete mParticles;
    mParticles = 0;
    
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

void Swarm::Init(void)
{
    for (int i=0; i<mNumberOfParticles; i++) {
        std::vector<float> points;
        std::vector<float> v_points;
        
        for (int x=0; x<mDimensions; x++)
        {
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
}

}

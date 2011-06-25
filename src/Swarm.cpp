#include "psocxx.hpp"


namespace psocxx {

Swarm::Swarm(const int& numberOfParticles)
    : mNumberOfParticles(numberOfParticles),
      mBestPosition(0),
      mBoundaryLo(0.0f),
      mBoundaryHi(0.0f)
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
    delete Helpers::Random::Instance();
}

void Swarm::ConfigureSpace(const int& dims, const float& lo, const float& hi)
{
    mDimensions = dims;
    mBoundaryLo = lo;
    mBoundaryHi = hi;
    
    Helpers::Random::Instance(lo, hi);
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
        
        for (int x=0; x<mDimensions; x++)
            points.push_back((float)Helpers::Random::Instance()->Generate());
        
        Vector position(points);
        Particle* p = new Particle(position);
        
        mParticles->push_back(p);
    }
}

}

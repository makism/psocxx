#ifndef _SWARM_HPP_ 
#define _SWARM_HPP_ 


namespace psocxx {

class Swarm {

public:
    Swarm(const int& numberOfParticles);
    ~Swarm(void);
    
    void ConfigureSpace(const int& dims, const float& lo = 0.0f, const float& hi = 1.0f);
    void SetParameters(const float& omega, const float& phi_p, const float& phi_g);
    void Init(void);
    
    Vector* BestPosition() const;
    void SetBestPosition(const Vector& position);

protected:
    std::vector<Particle *>* mParticles;
    
    int mNumberOfParticles;
    
    int mDimensions;
    float mBoundaryLo;
    float mBoundaryHi;
    
    float mParamOmega;
    float mParamPhiP;
    float mParamPhiG;
    
    Vector* mBestPosition;
};

}

#endif

#ifndef _SWARM_HPP_ 
#define _SWARM_HPP_ 


namespace psocxx {

class Swarm {

public:
    Swarm(void);
    ~Swarm(void);
    
    Vector* BestPosition() const;
    void SetBestPosition(const Vector& position);

protected:
    std::vector<Particle *>* mParticles;
    
    Vector* mBestPosition;
};

}

#endif

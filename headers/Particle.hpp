#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_


namespace psocxx {
    
class Swarm;

class Particle {
    friend class Swarm;
    
public:
    static float EvaluateCallback(const Vector* v);
    
public:
    Particle(const Vector& position);
    Particle(const Vector& position, const Vector& velocity);
    Particle(const Particle& n);
    virtual ~Particle(void);

    long unsigned int Id(void) const;
    
    void Evaluate(void);
    
    const std::string ToString(void) const;

protected:
    /*! */
    Vector *mPosition;
    
    /*! */
    Vector *mVelocity;
    
    /*! */
    Vector *mBestPosition;
    
    /*! */
    Swarm *mParent;

    /*! */
    long unsigned int mId;

    /*! */
    static long unsigned int counter;
};

}

#endif

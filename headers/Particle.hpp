#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_


namespace psocxx {

class Particle {
public:
    Particle(void);
    Particle(const Vector& position);
    Particle(const Vector& position, const Vector& velocity);
    Particle(const Particle& n);
    virtual ~Particle(void);

    long unsigned int Id(void) const;
    
    const std::string ToString(void) const;

protected:
    /*! */
    Vector *mPosition;
    
    /*! */
    Vector *mVelocity;
    
    /*! */
    Vector *mBestPosition;

    /*! */
    long unsigned int mId;

    /*! */
    static long unsigned int counter;
};

}

#endif

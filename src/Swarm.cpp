#include "psocxx.hpp"


namespace psocxx {

// Reset id counter.
long unsigned int Particle::counter = 0;

/*
* Empty constructor.
*/
Particle::Particle(void)
        : mId(-1),
          mPosition(0),
          mVelocity(0)
{

}

/*
* Copy constructor.
*/
Particle::Particle(const Particle& n)
{
}

/*
* Create a node with the given position.
*/
Particle::Particle(const Vector& position, const Vector& velocity)
        : mId(Particle::counter++)
{
    mPosition = new Vector(position);
    mVelocity = new Vector(velocity);
}

/*
* Empty destructor.
*/
Particle::~Particle(void)
{
    delete mPosition;
    delete mVelocity;
}

/*
*
*/
const std::string Particle::ToString(void) const
{
    std::ostringstream oss;


    return oss.str();
}

/*
*
*/
long unsigned int Particle::Id(void) const
{
    return mId;
}

}

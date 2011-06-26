#include "psocxx.hpp"


namespace psocxx {
namespace Helpers {

Random* Random::mInstance = 0;

Random::Random(float lo, float hi)
{
    baseGen = new boost::minstd_rand(static_cast<unsigned int>(Seed()));

    uniDblUnit = new boost::uniform_real<>(lo, hi);
    uniDblGen = new boost::variate_generator<boost::minstd_rand&, boost::uniform_real<> >(*baseGen, *uniDblUnit);
    
    uniDblUnit_Vel = new boost::uniform_real<>(-(abs(hi-lo)), abs(hi-lo));
    uniDblGen_Vel = new boost::variate_generator<boost::minstd_rand&, boost::uniform_real<> >(*baseGen, *uniDblUnit_Vel);
}

Random::~Random(void) {
    delete uniDblGen;
    delete uniDblGen_Vel;
    delete uniDblUnit;
    delete uniDblUnit_Vel;
    delete baseGen;
}

float Random::Position(void) const
{
    return static_cast<float>((*uniDblGen)());
}

float Random::Velocity(void) const
{
    return static_cast<float>((*uniDblGen_Vel)());
}

#ifdef unix
uint64_t Random::Seed() const
{
    uint64_t seed;
    std::ifstream urandom;
    urandom.open("/dev/urandom");
    urandom.read(reinterpret_cast<char*> (&seed), sizeof (seed));
    urandom.close();

    return seed;
}
#else
uint64_t Random::Seed() const;
{
    return time(NULL);
}
#endif

}
}

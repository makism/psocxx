#include "psocxx.hpp"


namespace psocxx {
namespace Helpers {
Random::~Random(void) {
    delete uniDblGen;
    delete uniDblUnit;
    delete baseGen;
}

double Random::Generate(void) const {
    return (*uniDblGen)();
}

Random::Random(float lo, float hi) {
    baseGen = new boost::minstd_rand(static_cast<unsigned int>(Seed()));
    uniDblUnit = new boost::uniform_real<>(lo, hi);
    uniDblGen = new boost::variate_generator<boost::minstd_rand&, boost::uniform_real<> >(*baseGen, *uniDblUnit);
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

Random* Random::mInstance = 0;

}
}

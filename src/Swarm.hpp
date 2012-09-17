#ifndef _SWARM_HPP_
#define _SWARM_HPP_

#include <vector>
#include <boost/function.hpp>
#include <boost/utility.hpp>


namespace psocxx {

class Swarm : public boost::noncopyable {

public:
    friend class Particle;

public:
    Swarm(unsigned int numberOfParticles);
    ~Swarm();

    void configureSpace(unsigned int dims, float lo = 0.0f, float hi = 1.0f);
    void setParameters(float omega, float phi_p, float phi_g);
    void setFitnessCallback(boost::function<float (const vecf&)> callback);

    void init();
    void step();

    unsigned int numberOfParticles();
    std::vector<Particle>& particles();

    const vecf& bestPosition() const;
    float bestFitness() const;

private:
    psocxx::Helpers::Random* m_rand;

    // Fitness evaluation function;
    boost::function<float (const vecf&)> m_fitnessCallback;

    //
    unsigned int m_numParticles;

    //
    std::vector<Particle> m_particles;

    // Upper and lower boundaries;
    float m_boundLower;
    float m_boundUpper;

    //
    unsigned int m_dimensions;

    // Parameters;
    float m_omega;
    float m_phiG;
    float m_phiP;

    //
    vecf m_bestPosition;
    float m_bestFitness;
};

}

#endif

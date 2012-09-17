#include "psocxx.hpp"


namespace psocxx {

Swarm::Swarm(unsigned int numberOfParticles)
    : m_numParticles(numberOfParticles),
      m_bestFitness(INFINITY)
{
}

Swarm::~Swarm()
{
    delete m_rand;
}

void Swarm::configureSpace(unsigned int dims, float lo, float hi)
{
    m_dimensions = dims;
    m_boundLower = lo;
    m_boundUpper = hi;

    m_rand = Helpers::Random::Instance(lo, hi);
}

void Swarm::setParameters(float omega, float phi_p, float phi_g)
{
    m_omega = omega;
    m_phiP = phi_p;
    m_phiG = phi_g;
}

void Swarm::setFitnessCallback(boost::function<float (const vecf&)> callback)
{
    m_fitnessCallback = callback;
}

void Swarm::init()
{
    for (unsigned int i=0; i<m_numParticles; ++i) {
        vecf points(m_dimensions);
        vecf v_points(m_dimensions);

        for (unsigned int d=0; d<m_dimensions; ++d) {
            points[d] = m_rand->Position();
            v_points[d] = m_rand->Velocity();
        }

        Particle p(points, v_points);
        p.m_parent = this;
        p.evaluate(false);

        m_particles.push_back(p);
    }
}

void Swarm::step()
{
    BOOST_FOREACH(Particle & particle, m_particles) {
        float Rp = m_rand->UniformUnit();
        float Rg = m_rand->UniformUnit();

        vecf& pos = particle.position();
        vecf& bpos = particle.bestPosition();
        vecf& vel = particle.velocity();

        // Update velocity.
        vel *= m_omega;

        vecf temp = bpos;
        temp -= pos;
        temp *= m_phiP * Rp;
        vel += temp;

        vecf temp2 = m_bestPosition;
        temp2 -= pos;
        temp2 *= m_phiG * Rg;
        vel += temp2;

        // Update position.
        pos += vel;

        // Evaluate particle.
        particle.evaluate(true);
    }
}

unsigned int Swarm::numberOfParticles()
{
    return m_numParticles;
}

std::vector<Particle>& Swarm::particles()
{
    return m_particles;
}

const vecf& Swarm::bestPosition() const
{
    return m_bestPosition;
}

float Swarm::bestFitness() const
{
    return m_bestFitness;
}

}

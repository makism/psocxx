#include "psocxx.hpp"


namespace psocxx {

unsigned long int Particle::COUNTER = 0;

Particle::Particle(const vecf& position)
    : m_position(position),
      m_bestPosition(position),
      m_velocity(zero_vecf(position.size())),
      m_parent(0),
      m_fitness(0.0f),
      m_id(COUNTER++)
{
}

Particle::Particle(const vecf& position, const vecf& velocity)
    : m_position(position),
      m_bestPosition(position),
      m_velocity(velocity),
      m_parent(0),
      m_fitness(0.0f),
      m_id(COUNTER++)
{
}

void Particle::evaluate(bool step)
{
    m_fitness = m_parent->m_fitnessCallback(m_position);

    // Actual evaluation
    if (step) {
        float res2 = m_parent->m_fitnessCallback(m_bestPosition);

        if (m_fitness < res2) {
            m_bestPosition = m_position;

            if (res2 < m_parent->m_bestFitness) {
                m_parent->m_bestFitness = res2;
                m_parent->m_bestPosition = m_bestPosition;
            }
        }
    } else {
        if (m_parent->m_bestPosition.empty() ||
            m_fitness < m_parent->m_bestFitness) {
            m_parent->m_bestFitness = m_fitness;
            m_parent->m_bestPosition = m_position;
        }
    }
}

unsigned long Particle::id() const
{
    return m_id;
}

float Particle::fitness() const
{
    return m_fitness;
}

vecf& Particle::position()
{
    return m_position;
}

vecf& Particle::bestPosition()
{
    return m_bestPosition;
}

vecf& Particle::velocity()
{
    return m_velocity;
}

const std::string Particle::toString() const
{
    std::ostringstream oss;

    oss << "Position: " << m_position;
    oss << ", ";
    oss << "Velocity: " << m_velocity;
    oss << ", ";
    oss << "Best Position: " << m_bestPosition;

    return oss.str();
}

}

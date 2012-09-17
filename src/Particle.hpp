#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_


namespace psocxx {

class Swarm;

class Particle {
    friend class Swarm;

public:
    Particle(const vecf& position);
    Particle(const vecf& position, const vecf& velocity);

    void evaluate(bool step=false);

    long unsigned int id() const;
    float fitness() const;
    vecf& position();
    void setPosition(const vecf& newPosition);
    vecf& bestPosition();
    void setBestPosition(const vecf& newBestPosition);
    vecf& velocity();
    void setVelocity(const vecf& newVelocity);

    const std::string toString() const;

private:
    /*! */
    vecf m_position;

    /*! */
    vecf m_velocity;

    /*! */
    vecf m_bestPosition;

    /*! */
    Swarm *m_parent;

    /*! */
    float m_fitness;

    /*! */
    long unsigned int m_id;

    /*! */
    static long unsigned int COUNTER;
};

}

#endif

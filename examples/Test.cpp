#include "psocxx.hpp"

using namespace psocxx;

namespace psocxx {
    float Particle::EvaluateCallback(const Vector* v)
    {
        return Helpers::Random::Instance()->UniformUnit();
    }
}

int main(int argc, char** arv)
{
    Swarm *s = new Swarm(100);
    
    // Define a 3 dimentional space.
    // The boundaries: 0.5f (lower) and 1.5f (upper).
    s->ConfigureSpace(3, 0.5f, 1.5f);
    
    // Pass the parameters (omega, phi_p, phi_g).
    s->SetParameters(0.1f, 0.2f, 0.3f);
    
    // Create inital particles.
    s->Init();
    
    // Step one iteration.
    s->Step();
    
    
    
    delete s;

    return 0;
}

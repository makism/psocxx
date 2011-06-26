#include "psocxx.hpp"

using namespace psocxx;

namespace psocxx {
    float Particle::EvaluateCallback(const Vector* v)
    {
        return 0.0f;
    }
}

int main(int argc, char** arv)
{
    Swarm *s = new Swarm(100);
    
    // Define a 3 dimentional space.
    // The boundaries: 0.5f (lower) and 1.5f (upper).
    s->ConfigureSpace(3, 0.5f, 1.5f);
    
    // Pass the parameters (omega, phi_p, phi_g).
    s->SetParameters(0.0f, 0.0f, 0.0f);
    
    // Create inital particles.
    s->Init();
    
    
    delete s;

    return 0;
}

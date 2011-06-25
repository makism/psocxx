#include "psocxx.hpp"

using namespace psocxx;

int main(int argc, char** arv)
{
    Swarm *s = new Swarm(100);
    s->ConfigureSpace(3, 0.5f, 1.0f);
    s->SetParameters(0.0f, 0.0f, 0.0f);
    s->Init();
    
    delete s;
    
    return 0;
}

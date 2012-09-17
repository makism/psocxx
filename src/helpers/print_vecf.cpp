#include "psocxx.hpp"

std::ostream & operator<< (std::ostream & os, const vecf & vector)
{
    os << "[";

    for (vecf::const_iterator i = vector.begin();
         i != vector.end();
         ++i)
    {
        os << *i;

        if (i != vector.end() - 1)
            os << ", ";
    }

    os << "]";

    return os;
}

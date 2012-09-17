#ifndef _PSOCXX_HPP_
#define _PSOCXX_HPP_

#include <math.h>
#include <vector>
#include <deque>
#include <numeric>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#ifdef __linux__
#   include <time.h>
#else
#   include <windows.h>
#endif

#include <boost/foreach.hpp>
#include <boost/numeric/ublas/vector.hpp>
typedef boost::numeric::ublas::vector<float> vecf;
typedef boost::numeric::ublas::zero_vector<float> zero_vecf;

std::ostream & operator<< (std::ostream & os, const vecf & vector);


#include "src/helpers/Random.hpp"
#include "src/Particle.hpp"
#include "src/Swarm.hpp"

//#include "src/helpers/JetColorspace.hpp"

#endif

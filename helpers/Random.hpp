 #ifndef _PSOCXX_HELPERS_RANDOM_HPP_
 #define _PSOCXX_HELPERS_RANDOM_HPP_
 
 #ifdef unix
 #   include <fstream>
 #else
 #   include <ctime>
 #endif
 
 namespace psocxx {
     namespace Helpers {
         // Based on
         // http://www.mitchr.me/SS/exampleCode/boost/boostRandEx.cpp.html
         // and http://sci.tuomastonteri.fi/programming/cplus/wrapper-to-boost-random
         // !!! needs optimization !!!
         class Random {
             
         public:
             static Random* Instance(float lo=0.0f, float hi=1.0f)
             {
                 if (mInstance==0)
                     mInstance = new Random(lo, hi);
                 
                 return mInstance;
             }
             
         public:
             ~Random(void);
             
             float UniformUnit(void) const;
             float Position(void) const;
             float Velocity(void) const;
             
         private:
             Random(float lo, float hi);
             uint64_t Seed() const;
             
         private:
             static Random* mInstance;
             
             boost::minstd_rand * baseGen;
             
             boost::uniform_real<> * uniDblUnit;
             boost::variate_generator<boost::minstd_rand&, boost::uniform_real<> > * uniDblGen;
  
             boost::uniform_real<> * uniDblUnit_Pos;
             boost::variate_generator<boost::minstd_rand&, boost::uniform_real<> > * uniDblGen_Pos;
             
             boost::uniform_real<> * uniDblUnit_Vel;
             boost::variate_generator<boost::minstd_rand&, boost::uniform_real<> > * uniDblGen_Vel;
         };
     }
 }
 
#endif

#ifndef _JETCOLORSPACE_HPP_
#define _JETCOLORSPACE_HPP_

namespace psocxx {
    namespace Helpers {
        
        class JetColorspace {
            
        public:
            static float* Convert(const float& value)
            {
                float fourValue = 4.0f * value;
                float red  = Min(fourValue - 1.5f, -fourValue + 4.5f);
                float green= Min(fourValue - 0.5f, -fourValue + 3.5f);
                float blue  = Min(fourValue + 0.5f, -fourValue + 2.5f);
                
                float* jet = new float[3];
                jet[0] = Clamp(red);
                jet[1] = Clamp(green);
                jet[2] = Clamp(blue);
                
                return jet;
            }
            
        private:
            static float Clamp(float& value)
            {
                if (value < 0.0f)
                    value = 0.0f;
                
                if (value > 1.0f)
                    value = 1.0f;
                
                return value;
            }
            
            static float Min(const float& x1, const float& x2)
            {
                if (x1 < x2)
                    return x1;
                else
                    return x2;
            }
            
        };
        
    }
}

#endif

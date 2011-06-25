#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_


namespace psocxx 
{

class Vector
{
public:
    Vector(void);
    Vector(const int dimensions);
#ifndef __cplusplus_cli
    Vector(float p, ...);
#endif
    Vector(const float& x, const float& y, const float& z);
    Vector(const float& x, const float& y, const float& z, const float& w);
    Vector(const std::vector<float>& p);
    Vector(const float* points, int dimensions);
    Vector(const Vector& v);
    ~Vector(void);

    Vector  operator  -(Vector& v);
    Vector  operator  +(Vector& v);
    Vector  operator  *(const float mult);
    Vector  operator  /(const float dv);
    Vector& operator -=(Vector& v);
    Vector& operator +=(Vector& v);
    Vector& operator *=(const float mult);
    Vector& operator /=(const float dv);
    float&  operator [](int index);
    float   const& operator [](int index) const;
    bool    operator  >(const Vector& v) const;
    bool    operator  <(const Vector& v) const;
    bool    operator ==(const Vector& v) const;

    int Dimensions(void) const;
    std::vector<float>* Points(void) const;

    void    Fill(const float& value);
    float   Magnitude(void);
    float   Dot(const Vector& v) const;
    Vector  Cross(const Vector& v) const;
    void    Normalize(void);
    float   DistanceFrom(const Vector& v) const;

    static const Vector One(int dimensions);
    static const Vector Zero(int dimensions);
    
    const std::string ToString(void) const;

private:
    int mDimensions;

    std::vector<float>* mPoints;

    float mMagnitude;
    
    bool mHasCalculatedMagnitude;
    
    bool mIsNormalized;
};

}

#endif

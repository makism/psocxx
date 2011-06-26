#include "psocxx.hpp"


namespace psocxx
{

Vector::Vector(void)
        : mDimensions(0),
        mMagnitude(0.0f),
        mHasCalculatedMagnitude(false),
        mIsNormalized(false)
{
    mPoints = new std::vector<float>();
}

Vector::Vector(const int dimensions)
        : mDimensions(dimensions),
        mMagnitude(0.0f),
        mHasCalculatedMagnitude(false),
        mIsNormalized(false)
{
    mPoints = new std::vector<float>();
}

#ifndef __cplusplus_cli
Vector::Vector(float s, ...)
        : mDimensions(0),
        mMagnitude(0.0f),
        mHasCalculatedMagnitude(false),
        mIsNormalized(false)
{
    mPoints = new std::vector<float>();

    va_list ap;
    va_start(ap, s);

    while (s) {
        mPoints->push_back(s);
        mDimensions++;

        s = va_arg(ap, double);
    }

    va_end(ap);
}
#endif

Vector::Vector(const float& x, const float& y, const float& z)
        : mDimensions(3),
        mMagnitude(0.0f),
        mHasCalculatedMagnitude(false),
        mIsNormalized(false)
{
    mPoints = new std::vector<float>();
    mPoints->push_back(x);
    mPoints->push_back(y);
    mPoints->push_back(z);
}

Vector::Vector(const float& x, const float& y, const float& z, const float& w)
        : mDimensions(4),
        mMagnitude(0.0f),
        mHasCalculatedMagnitude(false),
        mIsNormalized(false)
{
    mPoints = new std::vector<float>();
    mPoints->push_back(x);
    mPoints->push_back(y);
    mPoints->push_back(z);
    mPoints->push_back(w);
}

Vector::Vector(const std::vector<float>& p)
        : mPoints(0),
        mMagnitude(0.0f),
        mHasCalculatedMagnitude(false),
        mIsNormalized(false)
{
    mDimensions = p.size();
    mPoints = new std::vector<float>(mDimensions);

    std::copy(p.begin(), p.end(), mPoints->begin());
}

Vector::Vector(const float* points, int dimensions)
        : mDimensions(dimensions),
        mMagnitude(0.0f),
        mHasCalculatedMagnitude(false),
        mIsNormalized(false)
{
    mPoints = new std::vector<float>(mDimensions);
    
    for (unsigned int i = 0; i < mDimensions; i++)
        mPoints->push_back(*(points + i));
}

Vector::Vector(const Vector& v)
{
    mDimensions = v.mDimensions;
    mMagnitude = v.mMagnitude;
    mHasCalculatedMagnitude = v.mHasCalculatedMagnitude;
    mIsNormalized = v.mIsNormalized;

    mPoints = new std::vector<float>(mDimensions);

    std::copy(v.mPoints->begin(), v.mPoints->end(), mPoints->begin());
}

Vector::~Vector(void)
{
    delete mPoints;
}

float Vector::Magnitude(void)
{
    if (!mHasCalculatedMagnitude) {
        mMagnitude = sqrt(std::inner_product(mPoints->begin(), mPoints->end(), mPoints->begin(), 0.0f));

        mHasCalculatedMagnitude = true;
    }

    return mMagnitude;
}

void Vector::Normalize(void)
{
    if (!mIsNormalized)
        for (unsigned int i = 0; i < mDimensions; i++)
            mPoints->at(i) /= Magnitude();
}

void Vector::Fill(const float& value)
{
    for (unsigned int i = 0; i < mDimensions; i++)
        mPoints->push_back(value);
}

float Vector::DistanceFrom(const Vector& v) const
{
    float result = 0.0f;
    
    if (mDimensions == v.mDimensions) {
        for (int i=0; i<mDimensions; i++) {
            result += pow(mPoints->at(i) - v[i], 2);
        }
        
        result = sqrt(result);
    }
    
    return result;
}

float& Vector::operator [](int index)
{
    if (index < mDimensions)
        return mPoints->at(index);
}

float const& Vector::operator [](int index) const
{
    if (index < mDimensions)
        return mPoints->at(index);
}

Vector& Vector::operator *=(const float mult)
{
    for (int i=0; i<mDimensions; i++)
        (*mPoints)[i] *= mult;
    
    return *this;
}

Vector& Vector::operator -=(Vector& v)
{
    for (int i=0; i<mDimensions; i++)
        (*mPoints)[i] -= v[i];
    
    return *this;
}

Vector& Vector::operator +=(Vector& v)
{
    for (int i=0; i<mDimensions; i++)
        (*mPoints)[i] += v[i];
    
    return *this;
}

const Vector Vector::One(int dimensions)
{
    Vector v(dimensions);
    v.Fill(1.0f);

    return v;
}

const Vector Vector::Zero(int dimensions)
{
    Vector v(dimensions);
    v.Fill(0.0f);

    return v;
}

const std::string Vector::ToString(void) const
{
    std::ostringstream oss;

    oss << "Vector" << mDimensions << " (";

    for (int i=0; i<mDimensions; i++) {
        oss << mPoints->at(i);

        if (i < mDimensions-1)
            oss << ", ";
    }

    oss << ")";

    return oss.str();
}

}

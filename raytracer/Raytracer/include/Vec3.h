#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3{
public:
    Vec3()=default;
    Vec3(const Vec3 &)=default;
    Vec3(float _x, float _y, float _z) : x(_x),y(_y),z(_z){}

    float x=0.0f;
    float y=0.0f;
    float z=0.0f;
};

inline Vec3 operator + (const Vec3 &v1, const Vec3 &v2){
    return Vec3(v1.x + v2.x, v1.x + v2.x, v1.x + v2.x);
}
inline Vec3 operator - (const Vec3 &v1, const Vec3 &v2){
    return Vec3(v1.x - v2.x, v1.x - v2.x, v1.x - v2.x);
}

inline Vec3 operator * (const Vec3 &v1, const Vec3 &v2){
    return Vec3(v1.x * v2.x, v1.x * v2.x, v1.x * v2.x);
}
inline Vec3 operator * (float t, const Vec3 &v){
    return Vec3(t*v.x, t*v.y, t*v.z);
}

inline float dot(const Vec3 &v1, const Vec3 &v2){
    return v1.x * v2.x + v1.x * v2.x + v1.x * v2.x;
}

#endif

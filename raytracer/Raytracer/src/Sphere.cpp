#include "Sphere.h"
#include <eigen3/Eigen/Geometry>

Sphere::Sphere(const Eigen::Vector3f _v, float _r) :
    m_position(_v), m_radius(_r){

}

float Sphere::getRadius() const{
    return m_radius;
}

bool Sphere::hit(Eigen::Vector3f p, Eigen::Vector3f d, float &t, Eigen::Vector3f &q) const{
    //p = position. d = direction ::: // Ray = p + td, |d| = 1
    // if an intersection is found -> returns t value of intersection & intersection Eigen::Vector3f q
    Eigen::Vector3f m = p - m_position;
    float b = m.dot(d);
    float c = m.dot(m) - m_radius * m_radius;

    // Exit when origin is outside the circle (c > 0) and ray is pointing away from sphere (b > 0)
    if (c > 0.0f && b > 0.0f) return 0;
    float discriminant = b*b - c;

    //negative discriminant  = ray misses the sphere
    if (discriminant < 0.0f) return 0;

    // Ray intersects sphere, compute smallest t value of collision
    t = -b - sqrt(discriminant);

    // If t is negative, ray started in the sphere so make t zero
    if (t < 0.0f) t = 0.0f;
    q = p + t * d;

    return 1;
}

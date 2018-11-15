#ifndef SPHERE_H_
#define SPHERE_H_
#include "Vec3.h"
#include <eigen3/Eigen/Geometry>

class Sphere{
public:
    Sphere()=default;
    Sphere(const Eigen::Vector3f position, const float radius);

    float getRadius() const;
    bool hit(Eigen::Vector3f p, Eigen::Vector3f d, float &t, Eigen::Vector3f &q) const;

private:
    float m_radius = 0.0f;
    Eigen::Vector3f m_position;
};

#endif

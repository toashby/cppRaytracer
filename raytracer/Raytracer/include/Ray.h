#ifndef RAY_H_
#define RAY_H_
#include "Vec3.h"
#include <eigen3/Eigen/Geometry>

class Ray{
public:
    Ray()=default;
    Ray(const Eigen::Vector3f position, const Eigen::Vector3f direction);

    Eigen::Vector3f getDirection() const;
    Eigen::Vector3f getPosition() const;

private:
    Eigen::Vector3f m_position;
    Eigen::Vector3f m_direction;
};

#endif // HIT_H

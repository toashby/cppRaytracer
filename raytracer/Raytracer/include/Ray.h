#ifndef RAY_H_
#define RAY_H_
//#include "Vec3.h"
#include <eigen3/Eigen/Geometry>

class Ray{
public:
    Ray()=default;
    Ray(const Eigen::Vector3f origin, const Eigen::Vector3f direction);

    Eigen::Vector3f origin() const {return m_origin;}
    Eigen::Vector3f direction() const {return m_direction;}

    Eigen::Vector3f pointAtParameter(float t) const {
        return m_origin + t * m_direction;
    }

    Eigen::Vector3f m_origin;
    Eigen::Vector3f m_direction;

private:

};

#endif // HIT_H

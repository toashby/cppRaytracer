#include "Ray.h"
#include <eigen3/Eigen/Geometry>

Ray::Ray(const Eigen::Vector3f _v, Eigen::Vector3f _d) :
    m_position(_v), m_direction(_d){

}

Eigen::Vector3f Ray::getDirection() const{
    return m_direction;
}

Eigen::Vector3f Ray::getPosition() const{
    return m_position;
}

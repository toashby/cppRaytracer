#include "Ray.h"
#include <eigen3/Eigen/Geometry>

Ray::Ray(const Eigen::Vector3f _v, Eigen::Vector3f _d) :
    m_origin(_v), m_direction(_d){

}

//Eigen::Vector3f Ray::direction() const{
//    return m_direction;
//}

//Eigen::Vector3f Ray::origin() const{
//    return m_origin;
//}



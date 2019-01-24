/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 28/12/18 \n

/// \class Ray
/// \brief A simple ray class with origin and direction vectors

#ifndef RAY_H_
#define RAY_H_

#include <eigen3/Eigen/Geometry>

class Ray
{
public:
    Ray()=default;
    Ray(const Eigen::Vector3f origin, const Eigen::Vector3f direction);

    /// @brief return origin
    Eigen::Vector3f origin() const {return m_origin;}
    /// @brief return direction
    Eigen::Vector3f direction() const {return m_direction;}

    /// @brief fretch a point at specified distance along the ray
    /// @param[in] _t the distace
    Eigen::Vector3f pointAtParameter(float _t) const
    {
        return m_origin + _t * m_direction;
    }

    /// @brief the ray origin
    Eigen::Vector3f m_origin;
    /// @brief the ray direction
    Eigen::Vector3f m_direction;

private:

};

#endif // HIT_H

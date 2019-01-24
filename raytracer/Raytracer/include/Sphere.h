/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 15/12/18 \n

/// \class Sphere
/// \brief A basic sphere class with a ray sphere hit method

#ifndef SPHERE_H_
#define SPHERE_H_

#include <iostream>

#include <eigen3/Eigen/Geometry>

#include "Geometry.h"
#include "Ray.h"

class Sphere : public Geometry
{
public:
    Sphere() {}
    Sphere(Eigen::Vector3f cen, float r, Material *m) : m_position(cen), m_radius(r), mat_ptr(m) {}

    /// @brief check if ray hits sphere
    /// @param[in] _r the ray
    /// @param[in] _t_min the minimum distance along ray
    /// @param[in] _t_max the max distance to check along ray
    /// @param[in] _rec a hit record to store information about the hit to reduce parameters passed
    bool hit(const Ray& _r, float _t_min, float _t_max, hit_record& _rec) const
    {
        Eigen::Vector3f oc = _r.m_origin - m_position;
        float a = _r.m_direction.dot(_r.m_direction);
        float b = oc.dot(_r.m_direction);
        float c = oc.dot(oc) - m_radius*m_radius;
        float discriminant = b*b - a*c;
        //std::cout << discriminant << std::endl;
        if (discriminant > 0)
        {
            float temp = (-b - sqrt(b*b-a*c))/a;
            if(temp < _t_max && temp > _t_min)
            {
                _rec.t = temp;
                _rec.p = _r.pointAtParameter(_rec.t);
                _rec.normal = (_rec.p - m_position) / m_radius;
                _rec.mat_ptr = mat_ptr;
                return true;
            }
            temp = (-b + sqrt(b*b-a*c))/a;
            if(temp < _t_max && temp > _t_min)
            {
                _rec.t = temp;
                _rec.p = _r.pointAtParameter(_rec.t);
                _rec.normal = (_rec.p - m_position) / m_radius;
                _rec.mat_ptr = mat_ptr;
                return true;
            }
        }
        return false;
    }

    /// @brief sphere position
    Eigen::Vector3f m_position;
    /// @brief sphere radius
    float m_radius = 0.0f;
    /// @brief pointer to a material
    Material *mat_ptr;

private:

};





#endif

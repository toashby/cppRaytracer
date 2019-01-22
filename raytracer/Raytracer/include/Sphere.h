#ifndef SPHERE_H_
#define SPHERE_H_
#include "Geometry.h"
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include "Ray.h"

class Sphere : public Geometry
{
public:
    Sphere() {}
    Sphere(Eigen::Vector3f cen, float r, Material *m) : m_position(cen), m_radius(r), mat_ptr(m) {}
    bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
    {
        Eigen::Vector3f oc = r.m_origin - m_position;
        float a = r.m_direction.dot(r.m_direction);
        float b = oc.dot(r.m_direction);
        float c = oc.dot(oc) - m_radius*m_radius;
        float discriminant = b*b - a*c;
        //std::cout << discriminant << std::endl;
        if (discriminant > 0)
        {
            float temp = (-b - sqrt(b*b-a*c))/a;
            if(temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.pointAtParameter(rec.t);
                rec.normal = (rec.p - m_position) / m_radius;
                rec.mat_ptr = mat_ptr;
                return true;
            }
            temp = (-b + sqrt(b*b-a*c))/a;
            if(temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.pointAtParameter(rec.t);
                rec.normal = (rec.p - m_position) / m_radius;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }

        return false;
    }

    Eigen::Vector3f m_position;
    float m_radius = 0.0f;
    Material *mat_ptr;

private:

};





#endif

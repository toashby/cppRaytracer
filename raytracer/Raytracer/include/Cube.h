#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>

#include <eigen3/Eigen/Geometry>

#include "Geometry.h"
#include "Ray.h"


/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 20/01/19 \n

/// \class Cube.h
/// \brief A Cube class. Currently only renders a single triangle
/// \todo render a full cube not one triangle

class Cube : public Geometry
{
public:
    //Cube() {}
    Cube(Material *m, Eigen::Vector3f v0, Eigen::Vector3f v1, Eigen::Vector3f v2) :mat_ptr(m), vert0(v0), vert1(v1), vert2(v2) {}

    /// @brief check if ray hits triangle
    /// @param[in] _r the ray
    /// @param[in] _t_min the minimum distance along ray
    /// @param[in] _t_max the max distance to check along ray
    /// @param[in] _rec a hit record to store information about the hit to reduce parameters passed
    bool hit(const Ray& _r, float _t_min, float _t_max, hit_record& _rec) const
    {
        Eigen::Vector3f edge1 = vert1 - vert0;
        Eigen::Vector3f edge2 = vert2 - vert0;
        Eigen::Vector3f h;
        Eigen::Vector3f s;
        Eigen::Vector3f q;
        double a, f, u, v;
        h = _r.m_direction.cross(edge2);
        a = edge1.dot(h);
        if(a > -_t_min && a < _t_min)
        {
            return false; //because ray is parallel to triangle
        }
        f = 1.0 /a;
        s = _r.m_origin - vert0;
        u = f * (s.dot(h));
        if(u < 0.0 || u > 1.0)
        {
            return false;
        }
        q = s.cross(edge1);
        v = f * _r.m_direction.dot(q);
        if(v < 0.0 || u + v > 1.0)
        {
            return false;
        }

        float t = f * edge2.dot(q);
        if(t > _t_min && t < _t_max)
        {
            _rec.t = t;
            _rec.p = _r.pointAtParameter(_rec.t);

            Eigen::Vector3f tp = vert0 - _rec.p;
            tp = tp.cross(vert1 - _rec.p);
            tp.normalize();
            _rec.normal = tp;

            _rec.mat_ptr = mat_ptr;
            return true; //Ray intersects triangle
        }else
        {
            return false;
        }
    }

    /// @brief the pointer to a material. Pointer so multiple objects can share a material
    Material *mat_ptr;
    /// @brief vertex 0 of the triangle
    Eigen::Vector3f vert0;
    /// @brief vertex 1 of the triangle
    Eigen::Vector3f vert1;
    /// @brief vertex 2 of the triangle
    Eigen::Vector3f vert2;

private:

};

#endif

#ifndef CUBE_H_
#define CUBE_H_
#include "Geometry.h"
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include "Ray.h"
#include <iostream>

class Cube : public Geometry
{
public:
    //Cube() {}
    Cube(Material *m, Eigen::Vector3f v0, Eigen::Vector3f v1, Eigen::Vector3f v2) :mat_ptr(m), vert0(v0), vert1(v1), vert2(v2) {}
    bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
    {
        Eigen::Vector3f edge1;
        Eigen::Vector3f edge2;
        Eigen::Vector3f h;
        Eigen::Vector3f s;
        Eigen::Vector3f q;
        double a, f, u, v;
        edge1 = vert1 - vert0;
        edge2 = vert2 - vert0;
        h = r.m_direction.cross(edge2);
        a = edge1.dot(h);
        if(a > -t_min && a < t_min)
        {
            return false; //parallel to tri
        }
        f = 1.0 /a;
        s = r.m_origin - vert0;
        u = f * (s.dot(h));
        if(u < 0.0 || u > 1.0)
        {
            return false;
        }
        q = s.cross(edge1);
        v = f * r.m_direction.dot(q);
        if(v < 0.0 || u + v > 1.0)
        {
            return false;
        }

        float t = f * edge2.dot(q);
        if(t > t_min && t < t_max)
        {
            rec.t = t;
            rec.p = r.pointAtParameter(rec.t);

            Eigen::Vector3f tp = vert0 - rec.p;
            tp = tp.cross(vert1 - rec.p);
            tp.normalize();
            rec.normal = tp;

            rec.mat_ptr = mat_ptr;
            return true;
        }else
        {
            return false;
        }
    }
    //Eigen::Vector3f m_position;
    Material *mat_ptr;
    Eigen::Vector3f vert0;
    Eigen::Vector3f vert1;
    Eigen::Vector3f vert2;

private:

};

#endif

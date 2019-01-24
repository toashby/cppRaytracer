#ifndef TRIOBJECT_H_
#define TRIOBJECT_H_

#include <iostream>

#include <eigen3/Eigen/Geometry>

#include <ngl/BBox.h>
#include <ngl/Obj.h>
#include <ngl/Vec3.h>

#include "Geometry.h"
#include "Ray.h"

class TriObject : public Geometry
{
public:
    TriObject(Material *m, std::string objName) : mat_ptr(m)
    {
        //load obj
        m_mesh.reset( new ngl::Obj("models/" + objName));
        m_mesh->createVAO();
        faceList = m_mesh->getFaceList();
        vertList = m_mesh->getVertexList();

        //m_mesh->CalcBB;
        ngl::BBox objBounds = m_mesh->getBBox();
        bbMin = Eigen::Vector3f(objBounds.minX(), objBounds.minY(), objBounds.minZ());
        bbMax = Eigen::Vector3f(objBounds.maxX(), objBounds.maxY(), objBounds.maxZ());
    }

    /// @brief check if ray hits faces of .obj
    /// @param[in] _r the ray
    /// @param[in] _t_min the minimum distance along ray
    /// @param[in] _t_max the max distance to check along ray
    /// @param[in] _rec a hit record to store information about the hit to reduce parameters passed
    bool hit(const Ray& _r, float _t_min, float _t_max, hit_record& _rec) const
    {
        Eigen::Vector3f tempR = _r.m_direction.normalized();
        Eigen::Vector3f fractionDir = Eigen::Vector3f(1.0f / tempR(0), 1.0f / tempR(1), 1.0f / tempR(2));
        float p1 = (bbMin(0) - _r.m_origin(0))*fractionDir(0);
        float p2 = (bbMax(0) - _r.m_origin(0))*fractionDir(0);
        float p3 = (bbMin(1) - _r.m_origin(1))*fractionDir(1);
        float p4 = (bbMax(1) - _r.m_origin(1))*fractionDir(1);
        float p5 = (bbMin(2) - _r.m_origin(2))*fractionDir(2);
        float p6 = (bbMax(2) - _r.m_origin(2))*fractionDir(2);

        float tmin = std::max(std::max(std::min(p1, p2), std::min(p3, p4)), std::min(p5, p6));
        float tmax = std::min(std::min(std::max(p1, p2), std::max(p3, p4)), std::max(p5, p6));

        if (tmax < 0)//behind ray
        {
            return false;
        }
        if (tmin > tmax)//no intersection
        {
            return false;
        }

        //AABB was a hit so check each triangle

        hit_record temp_rec;
        bool hitSomething = false;
        float closest_so_far = _t_max;

        for(unsigned int fc = 0; fc < faceList.size(); fc++)
        {
            float vin = faceList[fc].m_vert[0];
            Eigen::Vector3f vert0 = Eigen::Vector3f(vertList[vin][0], vertList[vin][1], vertList[vin][2]); // assign elements manually
            //std::cout << "triobjprint: " << vertList[vin0][0] << " " << vertList[vin0][1] << " " << vertList[vin0][2] << std::endl;
            vin = faceList[fc].m_vert[1];
            Eigen::Vector3f vert1 = Eigen::Vector3f(vertList[vin][0], vertList[vin][1], vertList[vin][2]); // assign elements manually
            vin = faceList[fc].m_vert[2];
            Eigen::Vector3f vert2 = Eigen::Vector3f(vertList[vin][0], vertList[vin][1], vertList[vin][2]); // assign elements manually

            if(triHit(_r, _t_min, closest_so_far, temp_rec, vert0, vert1, vert2)){
                hitSomething = true;
                closest_so_far = temp_rec.t;
                _rec = temp_rec;
            }
        }
        return hitSomething;
    }

    ///@brief triangle hit detection
    /// Modified from :-
    /// Tomas Möller and Ben Trumbore (1997). Möller–Trumbore intersection algorithm [online].
    /// [Accessed 2019]. Available from: "https://www.tandfonline.com/doi/abs/10.1080/10867651.1997.10487468".
    bool triHit(const Ray& _r, float _t_min, float _t_max, hit_record& _rec, Eigen::Vector3f _vert0, Eigen::Vector3f _vert1, Eigen::Vector3f _vert2) const
    {
        Eigen::Vector3f edge1;
        Eigen::Vector3f edge2;
        Eigen::Vector3f h;
        Eigen::Vector3f s;
        Eigen::Vector3f q;
        double a, f, u, v;
        edge1 = _vert1 - _vert0;
        edge2 = _vert2 - _vert0;
        h = _r.m_direction.cross(edge2);
        a = edge1.dot(h);
        if(a > -_t_min && a < _t_min)
        {
            return false; //parallel to triangle
        }
        f = 1.0 /a;
        s = _r.m_origin - _vert0;
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
                //t_max = t;
                _rec.t = t;
                _rec.p = _r.pointAtParameter(_rec.t);

                Eigen::Vector3f tp = _vert0 - _rec.p;
                tp = tp.cross(_vert1 - _rec.p);
                tp.normalize();
                _rec.normal = tp;

                _rec.mat_ptr = mat_ptr;

            return true;
        }else
        {
            return false;
        }
    }

    Material *mat_ptr;
    Eigen::Vector3f bbMin;
    Eigen::Vector3f bbMax;

private:

    std::unique_ptr<ngl::Obj> m_mesh;
    std::vector<ngl::Vec3> vertList;
    std::vector<ngl::Face> faceList;

};

#endif


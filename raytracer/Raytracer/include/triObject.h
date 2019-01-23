//Abstract - TODO
#ifndef TRIOBJECT_H_
#define TRIOBJECT_H_

#include <ngl/Vec3.h>
#include <ngl/Obj.h>
#include <ngl/BBox.h>
#include <eigen3/Eigen/Geometry>
#include "Geometry.h"
#include "Ray.h"
#include <iostream>

class triObject : public Geometry
{
public:
    triObject(Material *m, std::string objName) : mat_ptr(m)
    {
        std::cout << objName << std::endl;
        //load obj
        m_mesh.reset( new ngl::Obj(objName));
        m_mesh->createVAO();
        faceList = m_mesh->getFaceList();
        vertList = m_mesh->getVertexList();

        //m_mesh->CalcBB;
        ngl::BBox objBounds = m_mesh->getBBox();
        bbMin = Eigen::Vector3f(objBounds.minX(), objBounds.minY(), objBounds.minZ());
        bbMax = Eigen::Vector3f(objBounds.maxX(), objBounds.maxY(), objBounds.maxZ());
    }

    bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
    {
        Eigen::Vector3f tempR = r.m_direction.normalized();
        Eigen::Vector3f fractionDir = Eigen::Vector3f(1.0f / tempR(0), 1.0f / tempR(1), 1.0f / tempR(2));
        float t1 = (bbMin(0) - r.m_origin(0))*fractionDir(0);
        float t2 = (bbMax(0) - r.m_origin(0))*fractionDir(0);
        float t3 = (bbMin(1) - r.m_origin(1))*fractionDir(1);
        float t4 = (bbMax(1) - r.m_origin(1))*fractionDir(1);
        float t5 = (bbMin(2) - r.m_origin(2))*fractionDir(2);
        float t6 = (bbMax(2) - r.m_origin(2))*fractionDir(2);

        float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

        if (tmax < 0)//behind ray
        {
            //t = tmax;
            return false;
        }
        if (tmin > tmax)//no intersection
        {
            //t = tmax;
            return false;
        }

        //AABB was a hit so check each triangle

        hit_record temp_rec;
        bool hitSomething = false;
        float closest_so_far = t_max;

        for(unsigned int fc = 0; fc < faceList.size(); fc++)
        {
            float vin = faceList[fc].m_vert[0];
            Eigen::Vector3f vert0 = Eigen::Vector3f(vertList[vin][0], vertList[vin][1], vertList[vin][2]); // assign elements manually
            //std::cout << "triobjprint: " << vertList[vin0][0] << " " << vertList[vin0][1] << " " << vertList[vin0][2] << std::endl;
            vin = faceList[fc].m_vert[1];
            Eigen::Vector3f vert1 = Eigen::Vector3f(vertList[vin][0], vertList[vin][1], vertList[vin][2]); // assign elements manually
            vin = faceList[fc].m_vert[2];
            Eigen::Vector3f vert2 = Eigen::Vector3f(vertList[vin][0], vertList[vin][1], vertList[vin][2]); // assign elements manually

            if(triHit(r, t_min, closest_so_far, temp_rec, vert0, vert1, vert2)){
                hitSomething = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hitSomething;
    }

    bool triHit(const Ray& r, float t_min, float t_max, hit_record& rec, Eigen::Vector3f vert0, Eigen::Vector3f vert1, Eigen::Vector3f vert2) const
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
            return false; //parallel to triangle
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
                //t_max = t;
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

    Material *mat_ptr;
    Eigen::Vector3f bbMin;
    Eigen::Vector3f bbMax;

private:

    std::unique_ptr<ngl::Obj> m_mesh;
    std::vector<ngl::Vec3> vertList;
    std::vector<ngl::Face> faceList;

};

#endif


#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <eigen3/Eigen/Geometry>
#include "Ray.h"

/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 08/01/19 \n

/// \class Geometry.h
/// \brief Abstract geometry class

class Material;

struct hit_record
{
    float t;
    Eigen::Vector3f p;
    Eigen::Vector3f normal;
    Material *mat_ptr;
};

class Geometry
{
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec)const = 0;
};



#endif

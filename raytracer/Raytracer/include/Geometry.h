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

/// @brief struct to store hit information
struct hit_record
{
    float t;
    Eigen::Vector3f p;
    Eigen::Vector3f normal;
    Material *mat_ptr;
};

/// @brief abstract class geometry with virtual hit method. Inherited objects implement hit differently
class Geometry
{
public:

    /// @brief virtual hit method
    /// @param[in] _r the ray
    /// @param[in] _t_min the minimum distance along ray
    /// @param[in] _t_max the max distance to check along ray
    /// @param[in] _rec a hit record to store information about the hit to reduce parameters passed
    virtual bool hit(const Ray& _r, float _t_min, float _t_max, hit_record& _rec)const = 0;
};



#endif

#ifndef GEOMETRYLIST_H
#define GEOMETRYLIST_H

#include <iostream>
#include "Geometry.h"

/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 08/01/19 \n

/// \class GeometryList.h
/// \brief A simple geometry list class with find closest object method


class GeometryList: public Geometry
{
public:
    GeometryList() {}
    GeometryList(Geometry **l, int n) {list = l; list_size = n;}
    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
    Geometry **list;
    /// @brief size of the geometry list
    int list_size;
};

/// @brief loops through every geometry to check for the nearest ray intersection
/// @param[in] _r the ray
/// @param[in] _t_min the minimum distance along ray
/// @param[in] _t_max the max distance to check along ray
/// @param[in] _rec a hit record to store information about the hit to reduce parameters passed
/// @param[out] bool if anything is hit returns true
bool GeometryList::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    for(int i = 0; i < list_size; i++){
        if(list[i]->hit(r,t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif // GEOMETRYLIST_H

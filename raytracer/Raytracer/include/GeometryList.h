#ifndef GEOMETRYLIST_H
#define GEOMETRYLIST_H

#include "Geometry.h"
#include <iostream>

/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 08/01/19 \n

/// \class GeometryList.h
/// \brief A simple geometry list class with find closest object method
/// \todo

class GeometryList: public Geometry
{
public:
    GeometryList() {}
    GeometryList(Geometry **l, int n) {list = l; list_size = n;}
    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
    Geometry **list;
    int list_size;
};

bool GeometryList::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(int i = 0; i < list_size; i++){
        //std::cout << "index: " << i << std::endl;
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

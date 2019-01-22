#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#include <eigen3/Eigen/Geometry>
#include "Geometry.h"

class BoundingBox
{
public:
    //void CreateBoundingBox(Geometry g) const;

private:
    Eigen::Vector3f m_p1;
    Eigen::Vector3f m_p2;
};

#endif

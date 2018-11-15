#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#include <eigen3/Eigen/Geometry>

class BoundingBox{
public:
    CreateBoundingBox();

private:
    Eigen::Vector3f m_p1;
    Eigen::Vector3f m_p2;
};

#endif

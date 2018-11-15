#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <eigen3/Eigen/Geometry>
#include "Triangle.h"
#include <vector>

class Geometry{
public:
    std::vector<Triangle> getTriangles();

private:
    std::vector<Triangle> m_triangles;
};

#endif

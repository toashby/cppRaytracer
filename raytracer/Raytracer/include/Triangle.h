#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include <eigen3/Eigen/Geometry>

class Triangle
{
public:
    Triangle(Eigen::Vector3f p0, Eigen::Vector3f p1, Eigen::Vector3f p2);

    Eigen::Vector3f getP0();
    Eigen::Vector3f getP1();
    Eigen::Vector3f getP2();

private:
    Eigen::Vector3f m_p0;
    Eigen::Vector3f m_p1;
    Eigen::Vector3f m_p2;
};

#endif

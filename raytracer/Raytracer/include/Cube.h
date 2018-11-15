#ifndef CUBE_H_
#define CUBE_H_
#include <eigen3/Eigen/Geometry>

class Cube{
public:
    Cube()=default;
    Cube(float x, float y, float z);

    Eigen::Vector3f getPosition();


private:
    float m_xScale;
    float m_yScale;
    float m_zScale;

    Eigen::Vector3f m_position;
};

#endif

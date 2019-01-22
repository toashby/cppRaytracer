#ifndef LIGHT_H_
#define LIGHT_H_
#include <eigen3/Eigen/Geometry>

class Light
{
public:
    Light()=default;
    Light(Eigen::Vector3f pos, float intensity);

    Eigen::Vector3f getPosition();
    float getIntensity();
    void setIntensity(float i);

private:
    Eigen::Vector3f m_position;
    float m_intensity = 0;
};

#endif

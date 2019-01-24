/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 08/01/19 \n

/// \class GeometryList.h
/// \brief A simple geometry list class with find closest object method
/// \todo make light work. currently not used
/// \todo draw shadow rays to lights
///
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

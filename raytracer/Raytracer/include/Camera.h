#ifndef CAMERA_H_
#define CAMERA_H_
#include <eigen3/Eigen/Geometry>

class Camera{
public:
    Camera()=default;

    float getFieldOfView() const;
    Eigen::Vector3f getPosition();
    Eigen::Vector3f getDirection();
    bool getOrthographic();
    unsigned int getWidth();
    unsigned int getHeight();

private:
    float m_fieldOfView;
    Eigen::Vector3f m_position;
    Eigen::Vector3f m_direction;
    bool m_orthographic;
    unsigned int width;
    unsigned int height;
};

#endif

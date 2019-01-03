#ifndef CAMERA_H_
#define CAMERA_H_
#include <eigen3/Eigen/Geometry>
#include "Ray.h"

class Camera{
public:
    Camera() {
        lowerLeftCorner = Eigen::Vector3f(-2.0, -1.0, -1.0);
        horizontal = Eigen::Vector3f(4.0, 0.0, 0.0);
        vertical = Eigen::Vector3f(0.0, 2.0, 0.0);
        origin = Eigen::Vector3f(0.0, 0.0, 0.0);
    }
    Ray getRay(float u, float v){return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);}

    float getFieldOfView() const;
    Eigen::Vector3f getPosition();
    Eigen::Vector3f getDirection();
    bool getOrthographic();
    unsigned int getWidth();
    unsigned int getHeight();

private:
    Eigen::Vector3f origin;
    Eigen::Vector3f lowerLeftCorner;
    Eigen::Vector3f horizontal;
    Eigen::Vector3f vertical;
};

#endif

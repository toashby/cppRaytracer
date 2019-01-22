#ifndef CAMERA_H_
#define CAMERA_H_
#include <eigen3/Eigen/Geometry>
#include "Ray.h"

/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 10/01/19 \n

/// \class Camera.h
/// \brief A simple camera class with variable POV
/// \todo add camera rotation

class Camera
{
public:
    Camera(Eigen::Vector3f lookfrom, Eigen::Vector3f lookat, Eigen::Vector3f vup, float vfov, float aspect)
    {
        Eigen::Vector3f u, v, w;
        float theta = vfov*M_PI/180;
        float halfHeight = tan(theta/2);
        float halfWidth  = aspect*halfHeight;
        origin = lookfrom;
        w = lookfrom - lookat;
        w = w.normalized();
        u = vup.cross(w);
        u = u.normalized();
        v = w.cross(u);
        lowerLeftCorner = origin - halfWidth*u - halfHeight*v - w;//Z=-1 FOR NORMAL POV
        horizontal = 2*halfWidth*u;
        vertical = 2*halfHeight*v;
        //origin = Eigen::Vector3f(0.0, 0.0, 0.0);
    }
    Ray getRay(float u, float v){return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);}

private:
    Eigen::Vector3f origin;
    Eigen::Vector3f lowerLeftCorner;
    Eigen::Vector3f horizontal;
    Eigen::Vector3f vertical;
};

#endif

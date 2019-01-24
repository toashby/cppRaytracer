/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 10/01/19 \n

/// \class Camera.h
/// \brief A simple camera class with variable POV
/// \todo add camera rotation

#ifndef CAMERA_H_
#define CAMERA_H_

#include <eigen3/Eigen/Geometry>

#include "Ray.h"

class Camera
{
public:
    /// @brief initialise a camera
    /// @param[in] _lookFrom the camera position
    /// @param[in] _lookAt the look at vector
    /// @param[in] _vUp the up vector
    /// @param[in] _vFoc the vertical field of view
    /// @param[in] _aspect the aspect ratio
    Camera(Eigen::Vector3f _lookFrom, Eigen::Vector3f _lookAt, Eigen::Vector3f _vUp, float _vFov, float _aspect)
    {
        Eigen::Vector3f u, v, w;
        float theta = _vFov*M_PI/180;
        float halfHeight = tan(theta/2);
        float halfWidth  = _aspect*halfHeight;
        origin = _lookFrom;
        w = _lookFrom - _lookAt;
        w = w.normalized();
        u = _vUp.cross(w);
        u = u.normalized();
        v = w.cross(u);
        lowerLeftCorner = origin - halfWidth*u - halfHeight*v - w;
        horizontal = 2*halfWidth*u;
        vertical = 2*halfHeight*v;
    }

    /// @brief initialise a camera
    /// @param[in] _uPosition normalised float to describe where ray should intersect the horizontal of the image plane
    /// @param[in] _vPosition normalised float to describe where ray should intersect the vertical of the image plane
    /// @param[out] Ray the resulting ray from camera origin through the image plane
    Ray getRay(float _uPosition, float _vPosition){return Ray(origin, lowerLeftCorner + _uPosition*horizontal + _vPosition*vertical - origin);}

private:
    /// @brief the origin vector
    Eigen::Vector3f origin;
    /// @brief the lower left corner position of the image plane
    Eigen::Vector3f lowerLeftCorner;
    /// @brief the horizontal direction vector of the image plane
    Eigen::Vector3f horizontal;
    /// @brief the vertical direction vector of the image plane
    Eigen::Vector3f vertical;
};

#endif

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include <eigen3/Eigen/Geometry>

#include "Camera.h"
#include "Geometry.h"
#include "Light.h"

class Scene
{
public:
    Scene()=default;

    /// @brief x resolution of image
    int m_resx;
     /// @brief y resolution of image
    int m_resy;
     /// @brief the number of samples for each pixel
    int m_numSamples;

    /// @brief renders an image
    /// @param[in] _samples number of rays to cast per pixel
    /// @param[in] _xResolution width of image
    /// @param[in] _yResolution height of image
    void Render(int _samples, int _xResolution, int _yResolution);
};

#endif

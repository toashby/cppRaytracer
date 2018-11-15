#ifndef LOAD_H_
#define LOAD_H_
#include <eigen3/Eigen/Geometry>
#include <vector>
#include "Object.h"
#include "Light.h"

class Load{
public:
    Load()=default;

    std::vector<Light> getLights();
    std::vector<Object> getObjects();
    Camera getCamera();

private:
    std::vector<Light> lights;
    std::vector<Object> objects;
    Camera camera;
};

#endif

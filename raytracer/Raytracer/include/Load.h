#ifndef LOAD_H_
#define LOAD_H_
#include <eigen3/Eigen/Geometry>
#include <vector>
#include "Light.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include "Geometry.h"
#include "Sphere.h"

class Material;

class Load
{
public:
    Load()=default;

    //std::vector<Light> getLights();
    //std::vector<Object> getObjects();
    //Camera getCamera();

private:
    //std::vector<Light> lights;
    //std::vector<Object> objects;
    //Camera camera;
};

#endif

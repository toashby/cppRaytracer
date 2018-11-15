#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <eigen3/Eigen/Geometry>

class Material{
public:
    Material()=default;
    Material(float _r, float _s, Eigen::Vector3f colour);

    Eigen::Vector3f get();


private:
    float m_roughness;
    float m_specular;

    Eigen::Vector3f colour;
};

#endif

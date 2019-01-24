#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <eigen3/Eigen/Geometry>

#include "Geometry.h"

/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 15/01/19 \n
///
/// Revision History :
/// Initial Version 26/12/18

/// \class Material.h
/// \brief A simple abstract material class
/// \todo add dielectrics and specular

struct hit_record;

class Material
{
public:
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Eigen::Vector3f& attenuation, Ray& scattered) const = 0;
};

/// @brief calculate reflection vector
/// @param[in] _v the vector
/// @param[in] _n the normal
Eigen::Vector3f reflect(const Eigen::Vector3f& _v, const Eigen::Vector3f& _n)
{
    return _v - 2 * _v.dot(_n)*_n;
}

/// @brief vector describing a random position  in a unit sphere around the hit point for monte carlo integration
/// @param[out] Eigen::Vector3f a random position in a unit sphere above the hit point
Eigen::Vector3f randomInUnitSphere()
{
    Eigen::Vector3f p; //point
    do{//repeat until valid point is found
        p = 2.0 * Eigen::Vector3f(drand48(), drand48(), drand48()) - Eigen::Vector3f(1,1,1);
    }while ((p(0)*p(0) + p(1)*p(1) + p(2)*p(2)) >= 1.0);
    return p;
}


/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 20/01/19 \n

/// \class lambertian
/// \brief A lambertian diffuse material

class lambertian : public Material
{
public:
    lambertian(const Eigen::Vector3f& a) : m_albedo(a) {}
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Eigen::Vector3f& attenuation, Ray& scattered) const
    {
        Eigen::Vector3f target = rec.p + rec.normal + randomInUnitSphere();
        scattered = Ray(rec.p, target-rec.p);
        attenuation = m_albedo;
        return true;
    }

    Eigen::Vector3f m_albedo;
};


/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 20/01/19 \n

/// \class metal
/// \brief A metal material

class metal : public Material
{
public:
    metal(const Eigen::Vector3f& _a, float _f) : m_albedo(_a) {if (_f<1) m_roughness = _f; else m_roughness = 1; }
    virtual bool scatter(const Ray& _r_in, const hit_record& _rec, Eigen::Vector3f& _attenuation, Ray& _scattered) const
    {
        Eigen::Vector3f reflected = reflect(_r_in.direction().normalized(), _rec.normal);////
        _scattered = Ray(_rec.p, reflected + m_roughness * randomInUnitSphere());
        _attenuation = m_albedo;
        return (_scattered.direction().dot(_rec.normal) > 0);
    }
    Eigen::Vector3f m_albedo;
    float m_roughness;
};

#endif

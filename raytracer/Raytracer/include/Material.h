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

Eigen::Vector3f reflect(const Eigen::Vector3f& v, const Eigen::Vector3f& n)
{
    return v - 2 * v.dot(n)*n;
}


Eigen::Vector3f randomInUnitSphere()
{
    Eigen::Vector3f p;
    do{
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
    lambertian(const Eigen::Vector3f& a) : albedo(a) {}
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Eigen::Vector3f& attenuation, Ray& scattered) const
    {
        Eigen::Vector3f target = rec.p + rec.normal + randomInUnitSphere();
        scattered = Ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }

    Eigen::Vector3f albedo;
};


/// \author THOMAS ASHBY
/// \version 1.0
/// \date Last Revision 20/01/19 \n

/// \class metal
/// \brief A metal material

class metal : public Material
{
public:
    metal(const Eigen::Vector3f& a, float f) : albedo(a) {if (f<1) roughness = f; else roughness = 1; }
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Eigen::Vector3f& attenuation, Ray& scattered) const
    {
        Eigen::Vector3f reflected = reflect(r_in.direction().normalized(), rec.normal);////
        scattered = Ray(rec.p, reflected + roughness * randomInUnitSphere());
        attenuation = albedo;
        return (scattered.direction().dot(rec.normal) > 0);
    }
    Eigen::Vector3f albedo;
    float roughness;
};

#endif

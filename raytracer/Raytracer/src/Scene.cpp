#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Core>
#include "Ray.h"
#include "Sphere.h"
#include "Cube.h"
#include "Scene.h"
#include "GeometryList.h"
#include "Geometry.h"
#include "Camera.h"
#include "Material.h"
#include "TriObject.h"
#include <math.h>

#include <nlohmann/json.hpp>

Eigen::Vector3f color(const Ray& r, Geometry *world, int depth)
{
    hit_record rec;
    if(world->hit(r, 0.001f, INT_MAX, rec))//MAXFOAT doesn't work on some machines?
    {
        Ray scattered;
        Eigen::Vector3f attenuation;
        if(depth < 5 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            Eigen::Vector3f rcol = color(scattered, world, depth + 1);
            return Eigen::Vector3f(attenuation(0)*rcol(0), attenuation(1)*rcol(1), attenuation(2) * rcol(2));
        }
        else
        {
            return Eigen::Vector3f(0.0,0.0,0.0);
        }
    }
    else
    {
        Eigen::Vector3f unit_direction = r.direction();
        unit_direction = unit_direction.normalized();

        float t = 0.5f*(unit_direction(1) + 1.0f);
        return (1.0f-t)*Eigen::Vector3f(1.0f,1.0f,1.0f) + t*Eigen::Vector3f(0.5f,0.7f,1.0f);
    }
}

void Scene::Render(int samples, int xResolution, int yResolution)
{

    m_resx = xResolution;
    m_resy = yResolution;
    m_numSamples = samples;//samples

    std::ifstream i("scene.json");
    nlohmann::json j;
    i >> j;

    // get an iterator to the first element
    nlohmann::json::iterator it = j.begin();
    std::cout << j.size() << std::endl;
    Geometry *list[j.size()];

    for(int i = 0; i < j.size(); i++)
    {
        std::string oType = it->at("oType").dump(); //get as a string

        if(oType == "\"sphere\"")
        {
            if(it->at("mType") == "metal"){
                list[i] = new Sphere(Eigen::Vector3f(it->at("x"), it->at("y"), it->at("z")), it->at("radius"), new metal(Eigen::Vector3f(it->at("r"), it->at("g"), it->at("b")), it->at("roughness")));
            }
            if(it->at("mType") == "lambert"){
                list[i] = new Sphere(Eigen::Vector3f(it->at("x"), it->at("y"), it->at("z")), it->at("radius"), new lambertian(Eigen::Vector3f(it->at("r"), it->at("g"), it->at("b"))));
            }
        }else if(oType == "\"obj\"")
        {
            if(it->at("mType") == "metal"){
                list[i] = new TriObject(new metal(Eigen::Vector3f(it->at("r"), it->at("g"), it->at("b")), it->at("roughness")), it->at("name"));
            }
            if(it->at("mType") == "lambert"){
                list[i] = new TriObject(new lambertian(Eigen::Vector3f(it->at("r"), it->at("g"), it->at("b"))), (std::string)it->at("name"));
            }
        }
        it++;
    }

    Geometry *world = new GeometryList(list, j.size());
    Camera cam(Eigen::Vector3f(-0.4f,0.3f,2.2f), Eigen::Vector3f(0.0f,0.0f,-1.0f), Eigen::Vector3f(0.0f,1.0f,0.0f), 90, float(m_resx)/float(m_resy));
    //Camera cam(Eigen::Vector3f(0,0,2), Eigen::Vector3f(0,0,-4), Eigen::Vector3f(0,1,0), 90, float(resx)/float(resy));


    std::ofstream myfile;
    myfile.open ("out/example.ppm");
    myfile << "P3\n" << m_resx << " " << m_resy << "\n255\n"; //for ppm file

    for(int j = m_resy - 1; j >= 0; j--)
    {
        std::cout << 100-((float)j/(float)m_resy)*100 << "%" << std::endl;
        for(int i = 0; i < m_resx; i++)
        {
            Eigen::Vector3f col(0.0,0.0,0.0);
            for(int s=0; s<m_numSamples; s++)
            {
                float u = float(i + drand48())/float(m_resx);
                float v = float(j + drand48())/float(m_resy);

                Ray sdir = cam.getRay(u, v);
                col += color(sdir, world, 0);
            }
            col /= float(m_numSamples);
            col = Eigen::Vector3f(sqrt(col(0)), sqrt(col(1)), sqrt(col(2)));
            int ir = int(255.99f*col(0));
            int ig = int(255.99f*col(1));
            int ib = int(255.99f*col(2));
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    myfile.close();
    std::cout << "done!" << std::endl;
}

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
#include "triObject.h"
#include <math.h>

#include <nlohmann/json.hpp>

Eigen::Vector3f color(const Ray& r, Geometry *world, int depth)
{
    hit_record rec;
    if(world->hit(r, 0.001f, INT_MAX, rec))//MAXFOAT doesn't work on some machines?
    {
        Ray scattered;
        Eigen::Vector3f attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
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

void Scene::Render(int samples)
{
    std::ifstream i("file.json");
    nlohmann::json j;
    i >> j;
    std::cout << j.at("firstName") << std::endl;

    resx = 300;
    resy = 150;
    nsam = samples;//samples

    Geometry *list[6];
    //list[5] = new Sphere(Eigen::Vector3f(0,0,-1), 0.5, new lambertian(Eigen::Vector3f(0.8, 0.3, 0.3)));
    list[3] = new Sphere(Eigen::Vector3f(0.0f, -101.0f, -1.0f), 100, new metal(Eigen::Vector3f(0.5f, 0.5f, 0.8f), 0.02f));
    list[2] = new Sphere(Eigen::Vector3f(1.0f,0.0f,-1.0f),0.5f, new metal(Eigen::Vector3f(0.8f, 0.6f, 0.2f), 1.0f));
    list[4] = new Sphere(Eigen::Vector3f(-0.7f,0.0f,-2.0f), 0.5f, new metal(Eigen::Vector3f(0.4f, 0.8f, 0.2f), 0.1f));
    list[1] = new Cube(new lambertian(Eigen::Vector3f(0.8f, 0.5f, 0.8f)), Eigen::Vector3f(2.0f,1.0f,-2.0f), Eigen::Vector3f(-2.0f,0.5f,-2.0f), Eigen::Vector3f(0.0f,0.0f,-2.0f));//middle
    //list[2] = new Cube(new metal(Eigen::Vector3f(0.8, 0.2, 0.2), 0.02), Eigen::Vector3f(-1,0,-3), Eigen::Vector3f(-1.5,3,2), Eigen::Vector3f(-2,0,-1));//big back
    list[0] = new Cube(new lambertian(Eigen::Vector3f(0.2f, 0.8f, 0.4f)), Eigen::Vector3f(2.0f,1.0f,-1.0f), Eigen::Vector3f(-0.5f,0.5f,-1.0f), Eigen::Vector3f(0.0f,-0.4f,-1.0f));//front
    //list[6] = new Sphere(Eigen::Vector3f(0,1.5,-0.5), 0.5, new metal(Eigen::Vector3f(0.9, 0.2, 0.2), 0.1));
    list[5] = new triObject(new metal(Eigen::Vector3f(0.2f, 0.6f, 0.2f), 0.1f));

    Geometry *world = new GeometryList(list, 6);
    Camera cam(Eigen::Vector3f(-0.4f,0.3f,2.2f), Eigen::Vector3f(0.0f,0.0f,-1.0f), Eigen::Vector3f(0.0f,1.0f,0.0f), 90, float(resx)/float(resy));
    //Camera cam(Eigen::Vector3f(0,0,2), Eigen::Vector3f(0,0,-4), Eigen::Vector3f(0,1,0), 90, float(resx)/float(resy));


    std::ofstream myfile;
    myfile.open ("example.ppm");
    myfile << "P3\n" << resx << " " << resy << "\n255\n"; //for ppm file

    for(int j = resy - 1; j >= 0; j--)
    {
        std::cout << 100-((float)j/(float)resy)*100 << "%" << std::endl;
        for(int i = 0; i < resx; i++)
        {
            Eigen::Vector3f col(0.0,0.0,0.0);
            for(int s=0; s<nsam; s++)
            {
                float u = float(i + drand48())/float(resx);
                float v = float(j + drand48())/float(resy);

                Ray sdir = cam.getRay(u, v);
                col += color(sdir, world, 0);
            }
            col /= float(nsam);
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

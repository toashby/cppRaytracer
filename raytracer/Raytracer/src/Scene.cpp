#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Core>
#include "Ray.h"
#include "Sphere.h"
#include "Scene.h"
#include "GeometryList.h"
#include "Geometry.h"
#include "Camera.h"


Eigen::Vector3f randomInUnitSphere(){
    Eigen::Vector3f p;
    do{
        p = 2.0 * Eigen::Vector3f(drand48(), drand48(), drand48()) - Eigen::Vector3f(1,1,1);
    }while ((p(0)*p(0) + p(1)*p(1) + p(2)*p(2)) >= 1.0);
    return p;
}

Eigen::Vector3f color(const Ray& r, Geometry *world){
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        Eigen::Vector3f target = rec.p + rec.normal + randomInUnitSphere();
        return 0.5*color(Ray(rec.p, target-rec.p), world);
    }else{
        Eigen::Vector3f unit_direction = r.direction();
        unit_direction = unit_direction.normalized();

        float t = 0.5*(unit_direction(1) + 1.0);
        return (1.0-t)*Eigen::Vector3f(1.0,1.0,1.0) + t*Eigen::Vector3f(0.5,0.7,1.0);
    }
}

void Scene::Render()
{
    resx = 200;
    resy = 100;
    nsam = 25;

    std::ofstream myfile;
    myfile.open ("example.ppm");
    myfile << "P3\n" << resx << " " << resy << "\n255\n"; //for ppm file

    Geometry *list[2];
    list[0] = new Sphere(Eigen::Vector3f(0,0,-1), 0.5);
    list[1] = new Sphere(Eigen::Vector3f(0, -100.5, -1), 100);
    Geometry *world = new GeometryList(list, 2);
    Camera cam;

    for(int j = resy - 1; j >= 0; j--){
        for(int i = 0; i < resx; i++){
            Eigen::Vector3f col(0.0,0.0,0.0);
            for(int s=0; s<nsam; s++){
                float u = float(i + drand48())/float(resx);
                float v = float(j + drand48())/float(resy);

                Ray sdir = cam.getRay(u, v);
                //	Eigen::Vector3f p = sdir.pointAtParameter(2.0);
                col += color(sdir, world);
            }
            col /= float(nsam);
            col = Eigen::Vector3f(sqrt(col(0)), sqrt(col(1)), sqrt(col(2)));
            int ir = int(255.99*col(0));
            int ig = int(255.99*col(1));
            int ib = int(255.99*col(2));

            //std::cout << ir << " " << ig << "" << ib << "\n";
            myfile << ir << " " << ig << " " << ib << "\n";
            //std::cout << "looping" << std::endl;
        }
    }

    myfile.close();
    std::cout << "done!" << std::endl;
}

# Raytracer

![rt](https://github.com/toashby/raytracer/blob/master/raytracer/Raytracer/out/finalrender.png)

A basic ray tracer inspired by:  
ray tracing in a weekend by Peter Shirley : http://in1weekend.blogspot.com/2016/01/ray-tracing-in-one-weekend.html?m=1 [online].

Loads a preview of the scene to be rendered to an opengl view and then renders the scene using that same json file.

Currently capable of rendering spheres, triangles and triangulated obj files with both metal and lambertian materials.

images output as a ppm file to /out.

HOW TO RUN  
Clone the repositiory and open raytracerall.pro in qtcreator. Clean, build and run. A clean all may need to be performed in order to run. No external libraries are needed as eigen and nlohmann headers are included in the include folder.

alternatively launch the raytracer executable in the Raytracer folder.


ASE Final Submission  
My C++ Ray Tracer has evolved from its initial proposal thanks to various practical issues which arose during development and thanks to the advice given by Jon Macey in his video feedback. Initially I planned to have a triangle class but this was surplus to requirements. I instead stored the vertices within each object that needed them as a list which I could iterate through or look up with a face list. When hit detection is needed I pass the relevant triangle points to my hit detection algorithm and calculate edges for working out normal etcetera. I managed to implement most of what I outlined in the initial submission.

The Ray Tracer has anti aliasing with variable samples per pixel.
It is capable of light bounces with varying roughness on metal surfaces. I have used a variation of monte carlo path tracing. A random direction within a unit sphere above the hit point is chosen for the reflection bounce. The sphere size can be varied to alter the roughness of the material.
The reflection angle is worked out in the reflect() method in Material.h.

The Camera.h currently has a look from vector, look at vector, and up vector, field of view and an aspect ratio. It is quite complete but still lacking advanced rotation. It is a perspective camera with variable field of view.

The scene to be rendered is loaded from a JSON file (scene.json) using nlohmann’s header only JSON parser. It is then parsed and then the scene is displayed as a 3d preview using a std::vector of MeshData, which is a struct containing mesh information such as position and colour. The scene is drawn using a loop in the paintgl() method in NGLScene.cpp. When the user chooses to render the scene it is passed to the scene class which parses it to create a virtual representation of the scene, which is then traced.

In order to render multiple types of object with different material types I use runtime polymorphism. I have an abstract geometry class which my sphere, cube and triObject classes implement. I also have lambertian and metal which implement material.

Obj files are loaded with NGL as a face list and a vertex list. The program loops through the face list to find the vertices and calculates triangle edges with them. This is then used to check ray triangle collision. This was initially very slow for large models but it is slightly faster now thanks to my axis aligned bounding box implementation which runs before checking triangles. It would further benefit from multi threading or the ability to run on the GPU.

Future Work  
I wish to add lighting to my tracer but did not have enough time. I would either do this by drawing shadow rays from hit points to the lights and seeing if the intersect geometry, or by adding an emission material to assign to geometry to have geometric lighting. I favour the latter approach as it soft shadows easier. Use of more smart pointers with the objects and materials would make the program more readable and easier to manage.

Known issues  
In the opengl preview of the scene the camera is not entirely correct.
Obj files are still just displayed as teapots in the preview.
TriObject can not have a position, they will render at the origin. 


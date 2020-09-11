/*
   Copyright 2020 Daniel S. Buckstein and Robert S. Christensen

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	GPRO-Graphics1-TestConsole-main.cpp
	Main entry point source file for a Windows console application.

	Modified by: Robert Christensen
	Modified because: The directions said to
*/

#ifndef __cplusplus
#error "Project is C++ only. Does NOT support C." 
#endif

#include "camera.hpp"
#include "image.hpp"
#include "raytrace.hpp"

#include "moremath.inl"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int main(int const argc, char const* const argv[])
{
    std::cout << "Initializing camera..." << std::endl;

    Image viewport(16*20, 9*20, 255);
    Camera cam(viewport, 75.0f*DEG2RAD);
    
    //Test objects. Anything passed to Camera::render must be allocated
    //on heap to correctly render (polymorphism must take effect)
    std::cout << "Initializing test objects..." << std::endl;
    std::vector<Traceable*> objects;
    objects.push_back(new Sphere(Vector3::forward()*2, 0.5f));

    std::cout << "Raytracing..." << std::endl;
    cam.render(objects);

    //Release objects
    std::cout << "Cleaning up test objects..." << std::endl;
    for (int i = 0; i < objects.size(); i++) delete objects[i];
    objects.clear();

    //Write to (user-specified) file
    std::cout << "Enter output file: ";
    std::string tmp; getline(std::cin, tmp);
    std::ofstream fout(tmp);

    viewport.write_to(fout);
    
    fout.flush();
    fout.close();

    return 0;
}

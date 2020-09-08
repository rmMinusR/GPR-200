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

#include "image.hpp"
#include "color.hpp"
#include "attr.inl"

#include <iostream>
#include <fstream>
#include <string>

void setter(int& v, const int& tv) { v = tv+1; }
int getter(int& v) { return v; }

int main(int const argc, char const* const argv[])
{
    attr<int> test{getter, setter};

    attr<int> test2{
        attr_get(int) {
            return _state;
        },
        attr_set(int) {
            _state = value;
        }
    };

    std::cout << (int)test << std::endl;
    test = 0;
    std::cout << (int)test << std::endl;
    test = 2;
    std::cout << (int)test << std::endl;

    /*
    Image img(300, 300, 300);

    for (int x = 0; x < img.width; x++) for (int y = 0; y < img.height; y++) {
        img.pixel_at(x, y) = Color::FromRGB((float)x, (float)y, 0, img.color_space);
    }

    std::cout << "Enter save file: ";
    std::string tmp; getline(std::cin, tmp);
    std::ofstream fout(tmp);

    img.write_to(fout);

    fout.flush();
    fout.close();
    */

    return 0;
}

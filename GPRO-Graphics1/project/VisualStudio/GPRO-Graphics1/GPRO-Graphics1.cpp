/*
   Copyright 2020 Daniel S. Buckstein

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

#ifndef __cplusplus
#error "Project is C++ only. Does NOT support C." 
#endif

#include "color.hpp"

int main(const int argc, const char* const argv[]) {
    Color c1 = Color::FromRGB(1, 2, 3);
    Color c2 = Color::FromHSV(2, 3, 4);
    float3 dummy = c1 + c2;
    Color actualColorSum = dummy*2.4f;
    c1 = actualColorSum;
}
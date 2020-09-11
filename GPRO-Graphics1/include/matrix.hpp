#pragma once

/*
	Copyright 2020 Robert S. Christensen

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
	matrix.hpp

	Defines the Matrix class, a powerful (albeit overscoped) solution to
	arbitrary object transformation. Due to remnants of my Java programming,
	any advanced math functions are non-performant due to repeated memory
	allocation and deallocations

	Adapted from `Matrix` by myself, in `rm's Bukkit Common API` (private codebase available upon request)
*/

#include "vector.hpp"

#include <vector>

class matrix final {
private:
	//Contains all internal values. 1D to avoid "pointer-to-pointer" BS.
	//Should always be indexed through _ind, like image.
	float* const m;
	inline int _ind(int x, int y) const;

	//Private to force use of factory initialization
	matrix(int _size);
public:
	//Factory initializers
	static matrix Zero(int _size);
	static matrix Identity(int _size);
	static matrix Translate(Vector3 vec);
	//I could implement more (scale, shear, rotate) but I don't see a reason to

	//Matrices described by this class are square. This describes either of its dimensions.
	const int size;

	//Copy values, not pointer addresses
	matrix(const matrix& cpy);
	matrix& operator=(const matrix& rhs);

	//Ideally would be [] but C++ doesn't support 2D indices
	inline float& operator()(const int& x, const int& y)       { return m[_ind(x, y)]; }
	inline float        at_c(const int& x, const int& y) const { return m[_ind(x, y)]; }

	//Object transformation
	Vector3 TransformPoint (const Vector3& point ) const;
	Vector3 TransformVector(const Vector3& vector) const;

	//Bunch of costly advanced maths. More complex = more costly
	matrix Inverse() const;
	float Determinant() const;
	matrix DropXY(const int& x, const int& y) const;
	matrix Adjugate() const;
	matrix Cofactor() const;
	matrix Transpose() const;
	matrix Minors() const;
	matrix CheckerboardSign() const;

	matrix operator*=(matrix& rhs) const;
};
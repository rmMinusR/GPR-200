#include "matrix.hpp"

#include "moremath.inl"

#include <stdexcept>

inline int matrix::_ind(int x, int y) const
{
	if (x < 0 || x >= size || y < 0 || y >= size) throw std::invalid_argument("Index out of bounds!");
	return x + y * size;
}

Vector3 matrix::TransformPoint(const Vector3& point) const
{
	return Vector3(
		at_c(0,0)*point.x + at_c(1,0)*point.y + at_c(2,0)*point.z + at_c(3,0),
		at_c(0,1)*point.x + at_c(1,1)*point.y + at_c(2,1)*point.z + at_c(3,1),
		at_c(0,2)*point.x + at_c(1,2)*point.y + at_c(2,2)*point.z + at_c(3,2)
	);
}

Vector3 matrix::TransformVector(const Vector3& vector) const
{
	return Vector3(
		at_c(0,0)*vector.x + at_c(1,0)*vector.y + at_c(2,0)*vector.z,
		at_c(0,1)*vector.x + at_c(1,1)*vector.y + at_c(2,1)*vector.z,
		at_c(0,2)*vector.x + at_c(1,2)*vector.y + at_c(2,2)*vector.z
	);
}

matrix matrix::Inverse() const
{
	float det = Determinant();
	if(det == 0) throw std::runtime_error("This matrix has no inverse!");

	matrix adj = Adjugate();
	matrix out = Zero(size);
	for(int x = 0; x < size; x++) for(int y = 0; y < size; y++) out(x,y) = adj(x,y) / det;
	return out;
}

float matrix::Determinant() const
{
	//I'm lazy so it's hardcoded to save ambiguity. See comment under 'else' block
	if (size == 1) {
		//Is this even a matrix?
		return at_c(0,0);
	}
	else if (size == 2) {
		//ad-bc
		return at_c(0,0) * at_c(1,1) - at_c(0,1) * at_c(1,0);
	}
	else if (size == 3) {
		return at_c(0,0)*at_c(1,1)*at_c(2,2) + at_c(1,0)*at_c(2,1)*at_c(0,2) + at_c(2,0)*at_c(0,1)*at_c(1,2) - at_c(0,0)*at_c(2,1)*at_c(1,2) - at_c(1,0)*at_c(0,1)*at_c(2,2) - at_c(2,0)*at_c(1,1)*at_c(0,2);
	}
	else if (size == 4) {
		return    at_c(0,0) * DropXY(0, 0).Determinant()
				- at_c(1,0) * DropXY(1, 0).Determinant()
				+ at_c(2,0) * DropXY(2, 0).Determinant()
				- at_c(3,0) * DropXY(3, 0).Determinant();
	}
	else {
		//Recursively calculate determinant. This probably works but I haven't
		//tested it yet. I can probably remove the proverbial duct tape holding
		//the hot mess that was this method together, but I don't feel like doing
		//the thorough testing needed.
		float sum = 0;
		for (int i = 0; i < size; i++) sum += DropXY(i, 0).Determinant() * (i % 2 == 0 ? 1 : -1);
		return sum;
	}
}

matrix matrix::DropXY(const int& x, const int& y) const
{
	matrix out(size - 1);
	//Drops the column by writing certain values twice.
	//Inefficient and hard to read and probably needs revising
	for (int ix = 0; ix < size; ix++) for (int iy = 0; iy < size; iy++) {
		if (ix != x && iy != y) {
			out(ix<=x ? ix : ix-1, iy<=y ? iy : iy-1) = at_c(ix,iy);
		}
	}
	return out;
}

matrix matrix::Adjugate() const
{
	return Cofactor().Transpose();
}

matrix matrix::Cofactor() const
{
	return Minors().CheckerboardSign();
}

matrix matrix::Transpose() const
{
	matrix out(size);
	for(int x = 0; x < size; x++) for(int y = 0; y < size; y++) out(y,x) = at_c(x,y);
	return out;
}

matrix matrix::Minors() const
{
	matrix out(size);
	for(int x = 0; x < size; x++) for(int y = 0; y < size; y++) out(x,y) = DropXY(x,y).Determinant();
	return out;
}

matrix matrix::CheckerboardSign() const
{
	matrix out(size);
	for(int x = 0; x < size; x++) for(int y = 0; y < size; y++) out(x,x) = ( ((x^y)&1) == 1 )? -at_c(x, y) : at_c(x, y);
	return out;
}

matrix::matrix(int _size) :
	size{ _size },
	m{ new float[sq(_size * _size)] }
{
	//No initialization of values; this is done in factory methods
}

//Root of the root of most factory matrices
matrix matrix::Zero(int _size)
{
	if (_size < 1) throw std::invalid_argument("Matrices must be at least 1x1!");
	matrix out(_size);
	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			out(x, y) = 0; //Clear garbage data
		}
	}
	return out;
}

//The root of most factory matrices
matrix matrix::Identity(int _size)
{
	matrix out = matrix::Zero(_size);
	for (int x = 0; x < _size; x++) {
		for (int y = 0; y < _size; y++) {
			out(x, y) = (x==y)?1.0f:0.0f; //Initialize to the identity matrix
		}
	}
	return out;
}

matrix matrix::Translate(Vector3 vec)
{
	matrix out = Identity(4);
	out(3, 0) = vec.x;
	out(3, 1) = vec.y;
	out(3, 2) = vec.z;
	return out;
}

matrix::matrix(const matrix& cpy) :
	size(cpy.size),
	m{ new float[sq(cpy.size)] }
{
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			operator()(x, y) = cpy.at_c(x, y);
		}
	}
}

matrix& matrix::operator=(const matrix& rhs)
{
	int least_size = __min(rhs.size, size);
	for (int x = 0; x < least_size; x++) {
		for (int y = 0; y < least_size; y++) {
			operator()(x, y) = rhs.at_c(x, y);
		}
	}
	return *this;
}

matrix matrix::operator*=(matrix& rhs) const
{
	matrix out = matrix::Zero(size);
	for (int x = 0; x < size; x++) for (int y = 0; y < size; y++) {

		//Adapted from Matrix.RowColDot
		for (int i = 0; i < size; i++) out(x, y) += at_c(i, y) + rhs(x, i);

	}
	return out;
}

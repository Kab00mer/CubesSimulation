#include "dimensional_shapes.h"
#include <math.h>

static float Z_PRIME = 50; //Distance used for projecting 3D to 2D
static float W_PRIME = 50; //Distance used for pojecting 4D to 3D

//==================================================
//                    SHAPE
//==================================================

Shape::Shape() : dimension(0), verticies({}) {}

size_t Shape::getDimension() const { return dimension; }

void Shape::rotate(float radians) {}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Shape::returnLines() const { return {}; }

//==================================================
//               SQUARE (FLAT CUBE)
//==================================================
/* The following Square does a flipping motion.
   It rotates all 2 axis, and it is the
   result of this matrix multiplication:

   [cos(theta), -sin(theta)] x [x]
   [sin(theta),  cos(theta)]   [y]
*/

Square::Square() {
	dimension = 1;
	verticies = { //(X, Y)
		{1.0, 1.0},
		{1.0, -1.0},
		{-1.0, -1.0},
		{-1.0, 1.0}
	};
}

void Square::rotate(float radians) {
	for (auto v : verticies) {
		int x = v[0];
		int y = v[1];
		
		rotateX(radians, v, x, y);
		rotateY(radians, v, x, y);
	}
}

void Square::rotateX(float radians, std::vector<float>& vertex, int x, int y) {
	vertex[0] = x * cos(radians) - y * sin(radians); 
}

void Square::rotateY(float radians, std::vector<float>& vertex, int x, int y) {
	vertex[1] = x * sin(radians) + y * cos(radians);
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Square::returnLines() const {
	return {
		std::pair(std::pair(verticies[0][0], verticies[0][1]), std::pair(verticies[1][0], verticies[1][1])),
		std::pair(std::pair(verticies[1][0], verticies[1][1]), std::pair(verticies[2][0], verticies[2][1])),
		std::pair(std::pair(verticies[2][0], verticies[2][1]), std::pair(verticies[3][0], verticies[3][1])),
		std::pair(std::pair(verticies[3][0], verticies[3][1]), std::pair(verticies[0][0], verticies[0][1])),
	};
}

//==================================================
//	                    CUBE
//==================================================

/* The following Cube does a spinning motion.
   It rotates all 3 axis, and it is the
   result of this matrix multiplication:

   [1,     0,           0     ]   [cos(theta),  0, sin(theta)]   [cos(theta), -sin(theta), 0]   [x]
   [0, cos(theta), -sin(theta)] x [     0,      1,      0    ] x [sin(theta),  cos(theta), 0] x [y]
   [0, sin(theta),  cos(theta)]   [-sin(theta), 0, cos(theta)]   [    0,          0,       1]   [z] 
*/

Cube::Cube() { 
	dimension = 3;
	verticies = { //(X, Y, Z)
		{1.0, 1.0, 1.0},
		{1.0, 1.0, -1.0},
		{1.0, -1.0, 1.0},
		{1.0, -1.0, -1.0},
		{-1.0, 1.0, 1.0},
		{-1.0, 1.0, -1.0},
		{-1.0, -1.0, 1.0},
		{-1.0, -1.0, -1.0}
	};
}

void Cube::rotate(float radians) {
	for (auto v : verticies) {
		int x = v[0];
		int y = v[1];
		int z = v[2];
		
		rotateX(radians, v, x, y, z);
		rotateY(radians, v, x, y, z);
		rotateZ(radians, v, x, y, z);
	}
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Cube::returnLines() const {
	std::vector<std::pair<float, float> projectedVerts = project3DTo2D();
	std::vector<std::pair<std::pair<float, float>, std::pair<float, float>> lines;
	lines.reserve(verticies.size();

	//figure out algo for cube with points
	return lines;
}

void Cube::rotateX(float radians, std::vector<float>& vertex, int x, int y, int z) {
	vertex[0] = -y * cos(radians) * sin(radians) + z * sin(radians) + x * cos(radians) * cos(radians);
}
		
void Cube::rotateY(float radians, std::vector<float>& vertex, int x, int y, int z) {
	vertex[1] = y * cos(radians) * cos(radians) - y * sin(radians) * sin(radians) * sin(radians) - z * sin(radians) * cos(radians) 
		+ x * cos(radians) * sin(radians) + x * sin(radians) * sin(radians) * cos(radians);
}
	
void Cube::rotateZ(float radians, std::vector<float>& vertex, int x, int y, int z) {
	vertex[2] = y * sin(radians) * sin(radians) * cos(radians) + y * sin(radians) * cos(radians) + z * cos(radians) * cos(radians) 
		+ x * sin(radians) * sin(radians) - x * cos(radians) * cos(radians);
}

std::vector<std::pair<float, float>> Cube::project3DTo2D() const {
	std::vector<std::pair<float, float>> result;
	result.reserve(verticies.size());

	for (auto v : verticies) {
		float x = v[0] * Z_PRIME / v[2];
		float y = v[1] * Z_PRIME / v[2];
		result.emplace_back(std::pair(x, y));	
	}

	return result; 
}

//==================================================
//	                  HYPERCUBE
//==================================================

/* The following Hypercube completes a famous double rotation.
   It rotates all 4 axis, and it is the
   result of this matrix multiplication:

   [cos(theta),     0,           0,     -sin(theta) ]   [x]
   [    0,      cos(theta), -sin(theta),      0     ] x [y]
   [    0,      sin(theta),  cos(theta),      0     ]   [z]
   [sin(theta),     0,           0,      cost(theta)]   [w]
*/

Hypercube::Hypercube() {
	dimension = 4;
	verticies = { //(X, Y, Z, W)
		{1.0, 1.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, -1.0},
		{1.0, 1.0, -1.0, 1.0},
		{1.0, 1.0, -1.0, -1.0},
		{1.0, -1.0, 1.0, 1.0},
		{1.0, -1.0, 1,0, -1.0},
		{1.0, -1.0, -1.0, 1.0},
		{1.0, -1.0, -1.0, -1.0},
		{-1.0, 1.0, 1.0, 1.0},
		{-1.0, 1.0, 1.0, -1.0},
		{-1.0, 1.0, -1.0, 1.0},
		{-1.0, 1.0, -1.0, -1.0},
		{-1.0, -1.0, 1.0, 1.0},
		{-1.0, -1.0, 1.0, -1.0},
		{-1.0, -1.0, -1.0, 1.0},
		{-1.0, -1.0, -1.0, -1.0}
	};
}

void Hypercube::rotate(float radians) {
	for (size_t i = 0; i < verticies.size(); ++i) {
		int x = verticies[i][0];
		int y = verticies[i][1];
		int z = verticies[i][2];
		int w = verticies[i][3];
		
		rotateX(radians, verticies[i], x, w);
		rotateY(radians, verticies[i], y, z);
		rotateZ(radians, verticies[i], y, z);
		rotateW(radians, verticies[i], x, w);
	}
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Hypercube::returnLines() const {
	return {};//project3DTo2D(project4DTo3D());
}


void Hypercube::rotateX(float radians, std::vector<float>& vertex, int x, int w) {
	vertex[0] = x * cos(radians) - w * sin(radians);
}

void Hypercube::rotateY(float radians, std::vector<float>& vertex, int y, int z) {
	vertex[1] = y * cos(radians) - z * sin(radians);
}

void Hypercube::rotateZ(float radians, std::vector<float>& vertex, int y, int z) {
	vertex[2] = y * sin(radians) + z * cos(radians);
}

void Hypercube::rotateW(float radians, std::vector<float>& vertex, int x, int w) {
	vertex[0] = x * sin(radians) + w * cos(radians);
}

std::vector<std::tuple<float, float, float>> Hypercube::project4DTo3D() const {
	//crazy math stuff;
	return {};
}

std::vector<std::pair<int, int>> Hypercube::project3DTo2D(std::vector<std::tuple<float, float, float>> projectedVerts) const {
	std::vector<std::pair<float, float>> result;
	result.reserve(verticies.size());

	for (auto v : projectVerts) {
		float x = v[0] * Z_PRIME / v[2];
		float y = v[1] * Z_PRIME / v[2];
		result.emplace_back(std::pair(x, y));	
	}
	
	return result; 
}




























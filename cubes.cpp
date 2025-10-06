#include "cubes.h"
#include <math.h>

static float Z_PRIME = 6.0; //Distance used for projecting 3D to 2D
static float W_PRIME = 4.0; //Distance used for pojecting 4D to 3D

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
		float x = v[0];
		float y = v[1];
		
		rotateX(radians, v, x, y);
		rotateY(radians, v, x, y);
	}
}

void Square::rotateX(float radians, std::vector<float>& vertex, float x, float y) {
	vertex[0] = x * cos(radians) - y * sin(radians); 
}

void Square::rotateY(float radians, std::vector<float>& vertex, float x, float y) {
	vertex[1] = x * sin(radians) + y * cos(radians);
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Square::returnLines() const {
	return { //This is the combination of all lines relating to a square's points 
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
		float x = v[0];
		float y = v[1];
		float z = v[2];
		
		rotateX(radians, v, x, y, z);
		rotateY(radians, v, x, y, z);
		rotateZ(radians, v, x, y, z);
	}
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Cube::returnLines() const {
	std::vector<std::pair<float, float>> projectedVerts = project3DTo2D();

	return { //This is the combination of all lines relating to a cubes's points
		std::pair(projectedVerts[0], projectedVerts[1]),
		std::pair(projectedVerts[0], projectedVerts[2]),
		std::pair(projectedVerts[0], projectedVerts[4]),
		std::pair(projectedVerts[1], projectedVerts[3]),
		std::pair(projectedVerts[1], projectedVerts[5]),
		std::pair(projectedVerts[2], projectedVerts[3]),
		std::pair(projectedVerts[2], projectedVerts[6]),
		std::pair(projectedVerts[3], projectedVerts[7]),
		std::pair(projectedVerts[4], projectedVerts[5]),
		std::pair(projectedVerts[4], projectedVerts[6]),
		std::pair(projectedVerts[5], projectedVerts[7]),
		std::pair(projectedVerts[6], projectedVerts[7])
	};
}

void Cube::rotateX(float radians, std::vector<float>& vertex, float x, float y, float z) {
	vertex[0] = -y * cos(radians) * sin(radians) + z * sin(radians) + x * cos(radians) * cos(radians);
}
		
void Cube::rotateY(float radians, std::vector<float>& vertex, float x, float y, float z) {
	vertex[1] = y * cos(radians) * cos(radians) - y * sin(radians) * sin(radians) * sin(radians) - z * sin(radians) * cos(radians) 
		+ x * cos(radians) * sin(radians) + x * sin(radians) * sin(radians) * cos(radians);
}
	
void Cube::rotateZ(float radians, std::vector<float>& vertex, float x, float y, float z) {
	vertex[2] = y * sin(radians) * sin(radians) * cos(radians) + y * sin(radians) * cos(radians) + z * cos(radians) * cos(radians) 
		+ x * sin(radians) * sin(radians) - x * cos(radians) * cos(radians);
}

std::vector<std::pair<float, float>> Cube::project3DTo2D() const {
	std::vector<std::pair<float, float>> result;
	result.reserve(verticies.size());

	for (auto v : verticies) {
		float x = (v[0] * Z_PRIME) / (Z_PRIME + v[2]); 
		float y = (v[1] * Z_PRIME) / (Z_PRIME + v[2]);
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
		float x = verticies[i][0];
		float y = verticies[i][1];
		float z = verticies[i][2];
		float w = verticies[i][3];
		
		rotateX(radians, verticies[i], x, w);
		rotateY(radians, verticies[i], y, z);
		rotateZ(radians, verticies[i], y, z);
		rotateW(radians, verticies[i], x, w);
	}
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Hypercube::returnLines() const {
	std::vector<std::pair<float, float>> projectedVerts = project3DTo2D(project4DTo3D());

	return { //This is the combination of all lines relating to this hypercube's points
		std::pair(projectedVerts[0], projectedVerts[1]),
		std::pair(projectedVerts[0], projectedVerts[2]),
		std::pair(projectedVerts[0], projectedVerts[4]),
		std::pair(projectedVerts[0], projectedVerts[8]),
		std::pair(projectedVerts[1], projectedVerts[3]),
		std::pair(projectedVerts[1], projectedVerts[5]),
		std::pair(projectedVerts[1], projectedVerts[9]),
		std::pair(projectedVerts[2], projectedVerts[3]),
		std::pair(projectedVerts[2], projectedVerts[6]),
		std::pair(projectedVerts[2], projectedVerts[10]),
		std::pair(projectedVerts[3], projectedVerts[7]),
		std::pair(projectedVerts[3], projectedVerts[11]),
		std::pair(projectedVerts[4], projectedVerts[5]),
		std::pair(projectedVerts[4], projectedVerts[6]),
		std::pair(projectedVerts[4], projectedVerts[12]),
		std::pair(projectedVerts[5], projectedVerts[13]),
		std::pair(projectedVerts[6], projectedVerts[7]),
		std::pair(projectedVerts[6], projectedVerts[14]),
		std::pair(projectedVerts[7], projectedVerts[15]),
		std::pair(projectedVerts[8], projectedVerts[9]),
		std::pair(projectedVerts[8], projectedVerts[10]),
		std::pair(projectedVerts[8], projectedVerts[12]),
		std::pair(projectedVerts[9], projectedVerts[11]),
		std::pair(projectedVerts[9], projectedVerts[13]),
		std::pair(projectedVerts[10], projectedVerts[11]),
		std::pair(projectedVerts[10], projectedVerts[14]),
		std::pair(projectedVerts[11], projectedVerts[15]),
		std::pair(projectedVerts[12], projectedVerts[13]),
		std::pair(projectedVerts[12], projectedVerts[14]),
		std::pair(projectedVerts[13], projectedVerts[15]),
		std::pair(projectedVerts[14], projectedVerts[15])
	};
}


void Hypercube::rotateX(float radians, std::vector<float>& vertex, float x, float w) {
	vertex[0] = x * cos(radians) - w * sin(radians);
}

void Hypercube::rotateY(float radians, std::vector<float>& vertex, float y, float z) {
	vertex[1] = y * cos(radians) - z * sin(radians);
}

void Hypercube::rotateZ(float radians, std::vector<float>& vertex, float y, float z) {
	vertex[2] = y * sin(radians) + z * cos(radians);
}

void Hypercube::rotateW(float radians, std::vector<float>& vertex, float x, float w) {
	vertex[0] = x * sin(radians) + w * cos(radians);
}

std::vector<std::tuple<float, float, float>> Hypercube::project4DTo3D() const {
	std::vector<std::tuple<float, float, float>> result;

	for (auto v : verticies) {
		float x = (v[0] * W_PRIME) / (W_PRIME + v[3]);
		float y = (v[1] * W_PRIME) / (W_PRIME + v[3]);
		float z = (v[2] * W_PRIME) / (W_PRIME + v[3]);
		result.emplace_back(std::tuple(x, y, z));
	}

	return result; 
}

std::vector<std::pair<float, float>> Hypercube::project3DTo2D(std::vector<std::tuple<float, float, float>> projectedVerts) const {
	std::vector<std::pair<float, float>> result;
	result.reserve(verticies.size());

	for (auto v : projectedVerts) { 
		float x = (std::get<0>(v) * Z_PRIME) / (Z_PRIME + std::get<2>(v)); 
		float y = (std::get<1>(v) * Z_PRIME) / (Z_PRIME + std::get<2>(v));
		result.emplace_back(std::pair(x, y));	
	}
	
	return result; 
}




























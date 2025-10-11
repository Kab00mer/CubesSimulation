#include "cubes.h"
#include <math.h>

static const float Z_PRIME = 6.0; //Distance used for projecting 3D to 2D
static const float W_PRIME = 4.0; //Distance used for pojecting 4D to 3D
static const float EPSILON = 1e-6f; //To prevent division by zero

//==================================================
//                    SHAPE
//==================================================

Shape::Shape() : dimension(0), vertices({}) {}

size_t Shape::getDimension() const { return dimension; }

void Shape::rotate(float radians) {}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Shape::returnLines() const { return {}; }

//==================================================
//               SQUARE (FLAT CUBE)
//==================================================

Square::Square() {
	dimension = 2;
	vertices = { //(X, Y)
		{1.0f, 1.0f},
		{1.0f, -1.0f},
		{-1.0f, -1.0f},
		{-1.0f, 1.0f}
	};
}

void Square::rotate(float radians) {
	float cosine = std::cos(radians);
	float sine = std::sin(radians);

	for (auto &v : vertices) { //rotate using a 2x2 rotation matrix
		float x = v[0] * cosine - v[1] * sine;
		float y = v[0] * sine + v[1] * cosine;
		v[0] = x;
		v[1] = y;
	}
}

std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> Square::returnLines() const {
	return { //This is the combination of all lines relating to a square's points 
		std::pair(std::pair(vertices[0][0], vertices[0][1]), std::pair(vertices[1][0], vertices[1][1])),
		std::pair(std::pair(vertices[1][0], vertices[1][1]), std::pair(vertices[2][0], vertices[2][1])),
		std::pair(std::pair(vertices[2][0], vertices[2][1]), std::pair(vertices[3][0], vertices[3][1])),
		std::pair(std::pair(vertices[3][0], vertices[3][1]), std::pair(vertices[0][0], vertices[0][1])),
	};
}

//==================================================
//	                    CUBE
//==================================================

Cube::Cube() { 
	dimension = 3;
	vertices = { //(X, Y, Z)
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, -1.0f},
		{1.0f, -1.0f, 1.0f},
		{1.0f, -1.0f, -1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f, -1.0f},
		{-1.0f, -1.0f, 1.0f},
		{-1.0f, -1.0f, -1.0f}
	};
}

void Cube::rotate(float radians) {
	float cosine = std::cos(radians);
	float sine = std::sin(radians);

	for (auto &v : vertices) { //we rotate on around the X-axis, then Y-axis, then Z-axis
		float y = v[1] * cosine - v[2] * sine;
		float z = v[1] * sine + v[2] * cosine;
		v[1] = y;
		v[2] = z;

		float x = v[0] * cosine + v[2] * sine;
		z = -v[0] * sine + v[2] * cosine;
		v[0] = x;
		v[2] = z;

		x = v[0] * cosine - v[1] * sine;
		y = v[0] * sine + v[1] * cosine;
		v[0] = x;
		v[1] = y;	
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

std::vector<std::pair<float, float>> Cube::project3DTo2D() const {
	std::vector<std::pair<float, float>> result;
	result.reserve(vertices.size());

	for (auto &v : vertices) {
		float denominator = Z_PRIME + v[2];
		if (std::abs(denominator) <= EPSILON) { 
			if (denominator > 0) {
				denominator = EPSILON;
			} else {
				denominator = -EPSILON;
			}
		}	
		float x = (v[0] * Z_PRIME) / (denominator); 
		float y = (v[1] * Z_PRIME) / (denominator);
		result.emplace_back(std::pair(x, y));	
	}

	return result; 
}

//==================================================
//	                  HYPERCUBE
//==================================================

Hypercube::Hypercube() {
	dimension = 4;
	vertices = { //(X, Y, Z, W) 
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, -1.0f, 1.0f},
		{1.0f, 1.0f, -1.0f, -1.0f},
		{1.0f, -1.0f, 1.0f, 1.0f},
		{1.0f, -1.0f, 1.0f, -1.0f},
		{1.0f, -1.0f, -1.0f, 1.0f},
		{1.0f, -1.0f, -1.0f, -1.0f},
		{-1.0f, 1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f, -1.0f},
		{-1.0f, 1.0f, -1.0f, 1.0f},
		{-1.0f, 1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f, 1.0f, 1.0f},
		{-1.0f, -1.0f, 1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f, 1.0f},
		{-1.0f, -1.0f, -1.0f, -1.0f}
	};
}

void Hypercube::rotate(float radians) {
	float cosine = std::cos(radians);
	float sine = std::sin(radians);
	
	for (auto &v : vertices) { //rotate around a 4x4 matrix for double rotation
		float x = v[0] * cosine - v[3] * sine;
		float y = v[1] * cosine - v[2] * sine;
		float z = v[1] * sine + v[2] * cosine;
		float w = v[0] * sine + v[3] * cosine;
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
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
		std::pair(projectedVerts[5], projectedVerts[7]),
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

std::vector<std::tuple<float, float, float>> Hypercube::project4DTo3D() const {
	std::vector<std::tuple<float, float, float>> result;

	for (auto &v : vertices) {
		float denominator = Z_PRIME + v[3];
		if (std::abs(denominator) <= EPSILON) { 
			if (denominator > 0) {
				denominator = EPSILON;
			} else {
				denominator = -EPSILON;
			}
		}
		float x = (v[0] * W_PRIME) / denominator; 
		float y = (v[1] * W_PRIME) / denominator; 
		float z = (v[2] * W_PRIME) / denominator; 
		result.emplace_back(std::tuple(x, y, z));
	}

	return result; 
}

std::vector<std::pair<float, float>> Hypercube::project3DTo2D(std::vector<std::tuple<float, float, float>> projectedVerts) const {
	std::vector<std::pair<float, float>> result;
	result.reserve(vertices.size());

	for (auto &v : projectedVerts) { 
		float denominator = Z_PRIME + std::get<2>(v);
		if (std::abs(denominator) <= EPSILON) { 
			if (denominator > 0) {
				denominator = EPSILON;
			} else {
				denominator = -EPSILON;
			}
		}
		float x = (std::get<0>(v) * Z_PRIME) / denominator; 
		float y = (std::get<1>(v) * Z_PRIME) / denominator; 
		result.emplace_back(std::pair(x, y));	
	}
	
	return result; 
}

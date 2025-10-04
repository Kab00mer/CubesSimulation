#include "dimensional_shapes.h"

//==================================================
//                    SHAPE
//==================================================

Shape::Shape() : dimension(0), verticies({}) {}

size_t Shape::getDimension() { return dimension; }

void Shape::rotate(float radians) {}

std::vector<std::pair<int,int>> Shape::returnLines() { return {}; }

//==================================================
//                    SQUARE
//==================================================

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
	rotateX(radians);
	rotateY(radians);
}

void Square::rotateX(float radians) {
	//matrix mult;
}

void Square::rotateY(float radians {
	//matrix mult;
}

std::vector<std::pair<int, int>> Square::returnLines() {
	return {
		std::pair(verticies[0], verticies[1],),
		std::pair(verticies[1], verticies[2],),
		std::pair(verticies[2], verticies[3],),
		std::pair(verticies[3], verticies[0],),
	}
}

//==================================================
//	                    CUBE
//==================================================

Cube::Cube() { 
	dimension = 3;
	verticies = { //(X, Y, Z)
		{1.0, 1.0, 1.0},
		{1.0, 1.0, -1.0},
		{1.0, -1.0, -1.0},
		{1.0, -1.0, 1.0},
		{-1.0, 1.0, 1.0},
		{-1.0, 1.0, -1.0},
		{-1.0, -1.0, -1.0},
		{-1.0, -1.0, 1.0}
	};
}

void Cube::rotate(float radians) {
	rotateX(radians);
	rotateY(radians);
	rotateZ(radians);
}

std::vector<std::pair<int, int>> Cube::returnLines() {
	return project3DTo2D();
}

void Cube::rotateX(float radians) {
	//matrix mult;
}
		
void Cube::rotateY(float radians) {
	//matrix mult;
}
	
void Cube::rotateZ(float radians) {
	//matrix mult;
}

std::vector<std::pair<int, int>> Cube::project3DTo2D() {
	//math stuff
	return {};
}

//==================================================
//	                  HYPERCUBE
//==================================================


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
	rotateX(radians);
	rotateY(radians);
	rotateZ(radians);
	rotateW(radians);
}

std::vector<std::pair<int, int>> Hypercube::returnLines() {
	return project3DTo2D(project4DTo3D());
}


void Hypercube::rotateX(float radians) {
	//matrix mult;
}

void Hypercube::rotateY(float radians) {
	//matrix mult;
}

void Hypercube::rotateZ(float radians) {
	//matrix mult;
}

void Hypercube::rotateW(float radians) {
	//matrix mult;
}

std::vector<std::tuple<float,float,float>> Hypercube::project4DTo3D() {
	//crazy math stuff;
	return {};
}

std::vector<std::pair<int, int>> Hypercube::project3DTo2D(std::vector<std::tuple<float, float, float>>) {
	return {}; 
}




























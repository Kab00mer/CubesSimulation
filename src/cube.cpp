#include "cube.h"
#include <math.h>
#include <iostream>

static const double D_PRIME = 10.0; //Distance used for projecting down a dimension
static const double EPSILON = 1e-6; //To prevent division by zero

Cube::Cube(size_t d) {
	dimension = d;
	switch (dimension) {	
		case 0:
			vertices = {};
			lineMapping = {};
			break;
		case 1:
			vertices = {{0.0}};
			lineMapping = {};
			break;

		default:
			size_t vertexCount = 1;
			for(size_t i = 0; i < dimension; ++i) {
				vertexCount = vertexCount << 1;
			}

			vertices.reserve(vertexCount);

			for (size_t i = 0; i < vertexCount; ++i) {
				std::vector<double> currentPoint(dimension);
				for (size_t j = 0; j < dimension; ++j) {
					currentPoint[j] = i & (1 << j) ? 1.0 : -1.0;		
				}
				vertices.push_back(currentPoint);
			}

			for (size_t i = 0; i < vertexCount; ++i) {
				for (size_t j = i + 1; j < vertexCount; ++j) {
					bool once = false;
					bool onlyOneDifference = false;

					for (size_t k = 0; k < dimension; ++k) {
						if (vertices[i][k] != vertices[j][k]) {
							if (!once) {
								onlyOneDifference = true;
								once = true;
							} else {
								onlyOneDifference = false;
							}
						}
					}

					if (onlyOneDifference) {
						lineMapping.push_back(std::make_pair(i, j));	
					}
				}
			}

	}
}

size_t Cube::getDimension() const { return dimension; }

void Cube::rotate(double radian) {
	for (size_t j = 0; j < vertices.size(); ++j) {
		for (size_t i = 0; i < dimension - 1; ++i) {
			double prime1 = vertices[j][i] * cos(radian) 
				- vertices[j][i + 1] * sin(radian);
			double prime2 = vertices[j][i] * sin(radian) 
				+ vertices[j][i + 1] * cos(radian);

			vertices[j][i] = prime1;
			vertices[j][i + 1] = prime2;
		}
	}
}

std::vector<Line> Cube::returnLines() const { 
	size_t currentDimension = dimension;
	size_t vertexCount = vertices.size();
	std::vector<std::vector<double>> projectedVerts = vertices;	

	while (currentDimension > 2) {
		double currentDPrime = D_PRIME * currentDimension;
		for (std::vector<double>& vertex : projectedVerts) {
			double denominator = currentDPrime + vertex[currentDimension - 1];

			if (std::abs(denominator) <= EPSILON) { 
				if (denominator > 0) {
					denominator = EPSILON;
				} else {
					denominator = -EPSILON;
				}
			}	

			for (size_t i = 0; i < currentDimension - 1; ++i) {
				vertex[i] = (vertex[i] * currentDPrime) / denominator;
			}
		}

		--currentDimension;
	}

	std::vector<Line> lines(lineMapping.size());
	
	for (std::pair<size_t, size_t> vertexPair : lineMapping) {
		size_t first = vertexPair.first;
		size_t second = vertexPair.second;

		Line currentLine(projectedVerts[first][0], projectedVerts[first][1], 
				projectedVerts[second][0], projectedVerts[second][1]);
		lines.push_back(currentLine);
	}

	return lines; 
}

#ifndef CUBE_H 
#define CUBE_H 

#include <vector>
#include <cstddef>

struct Line {
	double x1, y1, x2, y2;

	Line() : x1(0), y1(0), x2(0), y2(0) {}
	Line(double firstX, double firstY, double secondX, double secondY) : x1(firstX),
		y1(firstY), x2(secondX), y2(secondY) {}
};

class Cube {
	public:
		Cube(size_t);
		size_t getDimension() const;
		void rotate(double);
		std::vector<Line> returnLines() const;
		
	private:
		size_t dimension;
		std::vector<std::vector<double>> vertices;	
		std::vector<std::pair<size_t, size_t>> lineMapping;
};

#endif

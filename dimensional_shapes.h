#ifndef DIMENSIONAL_SHAPES_H
#define DIMENSIONAL_SHAPES_H

#include <vector>
#include <utility>
#include <cstddef>

class Shape {
	public:
		Shape();
		size_t getDimension() const;
		virtual void rotate(float);
		virtual std::vector<std::pair<int, int>> returnLines();
		
	private:
		size_t dimension;
		std::vector<std::vector<float>> verticies;	
};

class Square : public Shape {
	public:
		Square();
		void rotate(float) override;
		std::vector<std::pair<int, int>> returnLines() override;

	private:
		void rotateX(float);
		void rotateY(float);
};

class Cube : public Shape {
	public:
		Cube();
		void rotate(float) override;
		std::vector<std::pair<int, int>> returnLines() override;

	private:
		void rotateX(float);
		void rotateY(float);
		void rotateZ(float);

		std::vector<std::pair<int, int>> project3DTo2D() const;
};

class Hypercube : public Shape {
	public:
		Hypercube();
		void rotate(float) override;
		std::vector<std::pair<int, int>> returnLines() override;

	private:
		void rorateX(float);
		void rotateY(float);
		void rotateZ(float);
		void rotateW(float);
		
		std::vector<std::tuple<float, float, float>> project4DTo3D() const;
		std::vector<std::pair<int, int>> project3DTo2D(std::vector<std::tuple<float, float, float>>) const;
};

#endif

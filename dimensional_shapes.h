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
		virtual std::vector<std::pair<std::pair<float, float>, std::pair<float,float>>> returnLines() const;
		
	protected:
		size_t dimension;
		std::vector<std::vector<float>> verticies;	
};

class Square : public Shape {
	public:
		Square();
		void rotate(float) override;
		std::vector<std::pair<std::pair<float, float>, std::pair<float,float>>> returnLines() const override;

	private:
		void rotateX(float, std::vector<float>&, int, int);
		void rotateY(float, std::vector<float>&, int, int);
};

class Cube : public Shape {
	public:
		Cube();
		void rotate(float) override;
		std::vector<std::pair<std::pair<float, float>, std::pair<float,float>>> returnLines() const override;

	private:
		void rotateX(float, std::vector<float>&, int, int, int);
		void rotateY(float, std::vector<float>&, int, int, int);
		void rotateZ(float, std::vector<float>&, int, int, int);

		std::vector<std::pair<int, int>> project3DTo2D() const;
};

class Hypercube : public Shape {
	public:
		Hypercube();
		void rotate(float) override;
		std::vector<std::pair<std::pair<float, float>, std::pair<float,float>>> returnLines() const override;

	private:
		void rotateX(float, std::vector<float>&, int, int, int, int);
		void rotateY(float, std::vector<float>&, int, int, int, int);
		void rotateZ(float, std::vector<float>&, int, int, int, int);
		void rotateW(float, std::vector<float>&, int, int, int, int);
		
		std::vector<std::tuple<float, float, float>> project4DTo3D() const;
		std::vector<std::pair<int, int>> project3DTo2D(std::vector<std::tuple<float, float, float>>) const;
};

#endif

#ifndef CUBES_H 
#define CUBES_H 

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
		std::vector<std::vector<float>> vertices;	
};

class Square : public Shape {
	public:
		Square();
		void rotate(float) override;
		std::vector<std::pair<std::pair<float, float>, std::pair<float,float>>> returnLines() const override;
};

class Cube : public Shape {
	public:
		Cube();
		void rotate(float) override;
		std::vector<std::pair<std::pair<float, float>, std::pair<float,float>>> returnLines() const override;

	private:
		std::vector<std::pair<float, float>> project3DTo2D() const;
};

class Hypercube : public Shape {
	public:
		Hypercube();
		void rotate(float) override;
		std::vector<std::pair<std::pair<float, float>, std::pair<float,float>>> returnLines() const override;

	private:
		std::vector<std::tuple<float, float, float>> project4DTo3D() const;
		std::vector<std::pair<float, float>> project3DTo2D(std::vector<std::tuple<float, float, float>>) const;
};

#endif

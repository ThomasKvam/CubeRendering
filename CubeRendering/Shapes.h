#pragma once
#include <vector>

struct Shape
{

	std::vector<float> positions;
	unsigned int sizeInBytes;

	std::vector<int> indicies;

};

class shapes
{
public:

	Shape cube(float sideLength);
	Shape rectangularPrism(float xLength, float yLength, float zLength);
	Shape sphere(float radius);
	Shape nBasePyramid(int n, float height);
	Shape cylinder(float radius, float height);
	
};


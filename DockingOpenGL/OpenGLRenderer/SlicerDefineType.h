#pragma once
#include <vector>

namespace slicer 
{

	struct BoundingBox
	{
		float min_x;
		float min_y;
		float max_x;
		float max_y;
	};


	struct Vertex
	{
		float x;
		float y;
	};

	struct Contour
	{
		int id;
		std::vector<Vertex> vertices;
	};


	struct Layer
	{
		int id;
		float z;
		std::vector<Contour> contours;
	};


	struct SlicedModel
	{
		std::vector<Layer> layers;
	};
	

}



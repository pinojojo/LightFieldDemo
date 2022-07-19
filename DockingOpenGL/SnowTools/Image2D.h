#pragma once
#include <vector>
namespace snowtools {

	class Image2D
	{
	public:
		int width = 0;
		int height = 0;
		std::vector<unsigned char> pixels;
	};

}


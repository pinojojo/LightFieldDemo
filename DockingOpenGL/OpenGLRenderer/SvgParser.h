#pragma once
#include <string>
#include "SlicerDefineType.h"

namespace slicer {


class SvgParser
{


public:
	void ParseModel(const char* path);

	void  ParseLayer(std::string& text,Layer& layer);
	void  ParseContour(std::string& text,Contour & contour);

	SlicedModel model;


};

}
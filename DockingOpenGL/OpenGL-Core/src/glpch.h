#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "GLCore/Core/Log.h"

#ifdef GLCORE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif


#define NUMBERS_PI atan(1.0f)*4.f
#define NUMBERS_ONEDEG atan(1.0f)/45.f
#define D_GET_NAME(A) # A
#define DBP(A) std::cout<<" debug "<< D_GET_NAME(A)<<" : " <<A<<std::endl;
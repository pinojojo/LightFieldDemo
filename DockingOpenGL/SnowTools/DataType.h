#pragma once
#include "concurrentqueue.h"
#include "Image2D.h"
#include <atomic>
#include "Ringbuffer.h"
namespace snowtools
{
	struct Float2
	{
		float x = 0;
		float y = 0;
	};

	struct Float3
	{
		float x = 0;
		float y = 0;
		float z = 0;
	};
	struct Float4
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};

	struct Double2 
	{
		double x = 0;
		double y = 0;
	};
	struct Double3
	{
		double x = 0;
		double y = 0;
		double z = 0;
	};
	struct Double4
	{
		double x = 0;
		double y = 0;
		double z = 0;
		double w = 0;
	};

	// Define Some Alias of ConcurrentQueue
	typedef moodycamel::ConcurrentQueue<int>				IntBuffer;
	typedef moodycamel::ConcurrentQueue<float>				FloatBuffer;
	typedef moodycamel::ConcurrentQueue<snowtools::Float2>	Float2Buffer;
	typedef moodycamel::ConcurrentQueue<snowtools::Float3>	Float3Buffer;
	typedef moodycamel::ConcurrentQueue<snowtools::Float4>	Float4Buffer;
	typedef moodycamel::ConcurrentQueue<snowtools::Image2D>	ImageBuffer;

	// 
	typedef std::atomic<snowtools::Float2>	Float2Atomic;
	typedef Ringbuffer<Float2,2>	Float2Ringbuffer;

	
}

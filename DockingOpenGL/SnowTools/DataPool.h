#pragma once

#include "DataType.h"

class DataPool
{
public:
	DataPool(const DataPool&) = delete;

	static DataPool& GetInstance() {
		static DataPool instance;
		return instance;
	}

	snowtools::Float2Buffer testBuffer;
	snowtools::Float2Atomic testBufferAtomic;
	snowtools::Float2Ringbuffer testRingbuffer;

private:
	DataPool(){}

	

};


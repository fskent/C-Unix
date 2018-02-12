//  sink.h
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "image.h"

#ifndef sink_h
#define sink_h

#include <stdlib.h>
#include <stdio.h>

class sink
{
	protected:
		const Image* input1;
		const Image* input2;
	public:
		sink();
		virtual const char* sinkName() = 0;
		void SetInput(Image* in);
		void SetInput2(Image* in2);
};

#endif
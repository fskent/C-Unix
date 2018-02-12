//  PNMwriter.h
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "sink.h"

#include <stdlib.h>
#include <stdio.h>

class PNMwriter:public sink
{
	public:
		void Write(char * filename);
		const char* sinkName();
};
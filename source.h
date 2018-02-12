//  source.h
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "image.h"

#ifndef source_h
#define source_h

#include <stdlib.h>
#include <stdio.h>

class source
{	
	public:	
		source();
		Image* GetOutput();
		//pure virtual function
		virtual void Update() = 0;
		virtual const char* sourceName() = 0;
	protected:
		Image img;
		//pure virtual function
		virtual void Execute(void) = 0;
};

#endif
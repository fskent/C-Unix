//  PNMreader.h
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "source.h"

#include <stdlib.h>
#include <stdio.h>

class PNMreader:public source
{
	private:
		char* readfile;
	public:
		PNMreader(char *filename);
		virtual void Execute();
		virtual void Update();
		const char* sourceName();
		char* getFile();
};
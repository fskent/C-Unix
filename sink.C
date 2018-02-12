//  sink.C
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "sink.h"
#include "logging.h"

#include <stdlib.h>
#include <stdio.h>

sink::sink()
{
	input1 = NULL; //these needed to be set to null to avoid memory errors
	input2 = NULL;
};

void sink::SetInput(Image* in)
{
	input1 = in;
};

void sink::SetInput2(Image* in2)
{
	input2 = in2;
};




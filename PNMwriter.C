//  PNMwriter.C
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "PNMwriter.h"
#include "logging.h"

#include <stdlib.h>
#include <stdio.h>

void PNMwriter::Write(char * filename)
{
	//open file
    FILE *f_out = fopen(filename, "wb");
    
    //hard code pnm file data
    fprintf(f_out, "P6\n%d %d\n%d\n", input1->getWidth(), input1->getHeight(), 255);
    
    //write binary information
    fwrite(input1->getPixel(), sizeof(unsigned char), input1->getWidth()*input1->getHeight()*3, f_out);
    
    //close file
    fclose(f_out);
};

const char* PNMwriter::sinkName()
{
	return ("PNMwriter");
};

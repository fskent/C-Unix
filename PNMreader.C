//  PNMreader.C
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "PNMreader.h"
#include "logging.h"

#include <stdlib.h>
#include <stdio.h>

PNMreader::PNMreader(char *filename)
{
	readfile = filename;
};

void PNMreader::Execute()
{
	//open file
    FILE *f_in;
    f_in = fopen(readfile, "rb");
    char magicNum[128];
    int maxval, width, height;
    //scan pnm documentation
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    //set the image and allocate space
    img.SetSize(width, height);
    
    //read pixel buffer data
    fread(img.getPixel(), sizeof(unsigned char), img.getWidth()*img.getHeight()*3, f_in);
    fclose(f_in);

};

char* PNMreader::getFile()
{
	return readfile;

};

void PNMreader::Update()
{
	char msg[128];
	sprintf(msg, "%s: about to execute", sourceName()); Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing", sourceName()); Logger::LogEvent(msg);
};

const char* PNMreader::sourceName()
{
	return ("PNMreader");
};
//  image.C
//
//  Created by Steve Kent on 5/23/17.
//
#include <stdlib.h>
#include <stdio.h>

#include "image.h"
#include "source.h"

Image::Image(Image &)
{
	//copy constructor
    pixel = (unsigned char*) malloc(width*height*3);
};

Image::Image()
{
  //void constructor
};

//parameterized constructor is defined in the header file

void Image::SetSize(int w, int h)
{
	//reset size method
    width = w;
    height = h;
    pixel = (unsigned char*) malloc(w*h*3);    
};

int Image::getWidth() const
{
	return width;
};

int Image::getHeight() const
{
	return height;
};

unsigned char* Image::getPixel() const
{
	return pixel;
};

void Image::setPixel()
{
	//allocate space for pixel
	pixel = (unsigned char*)malloc(width*height*3);
};

void Image::Update() const
{
	//Update will need to know about a created source object
	//Image also uses setsourceObject so it knows what to update
	//reference to source object can now be updated 
	if (sourceObject != NULL){
		sourceObject->Update();
	}
};

void Image::setsourceObject(source *sObject)
{
	sourceObject = sObject;
};
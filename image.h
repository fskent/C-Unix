//  image.h
//  
//  Created by Steve Kent on 5/23/17.
//  Retro fitted from 3A to exclude pixel struct and use a 3-dimensional array
//  3D array allow for more clarity when manipulating images
#ifndef image_h
#define image_h

#include <stdlib.h>
#include <stdio.h>

class source; //so image has a reference to sources

class Image
{
	private:
    	int width; //x
    	int height; //y
    	unsigned char* pixel; //pixel buffer
    	
    public:
    	Image(); //void constructor 
    	//removed Image destructor because it caused memory errors, will investigate later.
    	//~Image() {if (pixel != NULL) delete [] pixel; }; //destructor
    	Image(int w, int h) {width = w; height = h;}; //parameterized constructor
    	Image(Image &); //copy constructor
    	
    	//methods
    	void SetSize(int w, int h); //method to reset size
    	int getWidth() const;
    	int getHeight() const;
    	unsigned char* getPixel() const;
    	void setPixel();
    	
    	//Update and source object methods
    	void Update() const;
    	source *sourceObject;
    	void setsourceObject(source *sObject);   	
};

#endif /* image_h */
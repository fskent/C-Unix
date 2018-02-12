//  source.C
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last updated on 5/27/17
#include "source.h"
#include "image.h"
#include "logging.h"


#include <stdlib.h>
#include <stdio.h>

source::source()
{
	img.setsourceObject(this); //set images' source object reference
};

Image* source::GetOutput()
{
	return &img;
};




//  filters.C
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last update on 5/27/17
#include "source.h"
#include "sink.h"
#include "filters.h" 
#include "logging.h"

#include <stdlib.h>
#include <stdio.h>



void filter::Update()
{
    if (img.getHeight() == 0 || img.getWidth() == 0){
        char msg[1024];
        sprintf(msg, "Img height or width incorrect: h = %d, w = %d", img.getHeight(), img.getWidth());
        DataFlowException e(sinkName(), msg);
        throw e;
    }
	
	if (input1 != NULL){
		char msg[1024];
		sprintf(msg, "%s: about to update input", filterName());
		Logger::LogEvent(msg);
		input1->Update();
		sprintf(msg, "%s: done updating input", filterName());
		Logger::LogEvent(msg);
	}
	
	if (input2 != NULL){
		char msg[1024];
		sprintf(msg, "%s: about to update input2", filterName());
		Logger::LogEvent(msg);
		input2->Update();
		sprintf(msg, "%s: done updating input2", filterName());
		Logger::LogEvent(msg);	
	}
	
	char msg[1024];
	sprintf(msg, "%s: about to execute", filterName());
	Logger::LogEvent(msg);
	Execute(); //after updating, object can be executed
	sprintf(msg, "%s: done executing", filterName());
	Logger::LogEvent(msg);
};

const char* filter::sinkName()
{
	return filterName();
};

const char* filter::sourceName()
{	
	return filterName();
};



const char* Color::sourceName()
{
	return ("Color");
};



void Color::Execute()
{
	img.SetSize(width, height);
	int i, j;
	for  (i = 0; i < img.getHeight(); i++){
        for (j = 0; j < img.getWidth(); j++){
        	img.getPixel()[3*(i*(img.getWidth())+j)] = red;
        	img.getPixel()[3*(i*(img.getWidth())+j)+1] = green;
        	img.getPixel()[3*(i*(img.getWidth())+j)+2] = blue;
        }     
    }
};

void Color::Update()
{
	Execute();
};


const char* CheckSum::sinkName()
{
	return ("CheckSum");
};


void CheckSum::OutputCheckSum(const char *filename)
{
	FILE *f_out2 = fopen(filename, "wb");
	redCount = 0;
	greenCount = 0;
	blueCount = 0;
	int i, j;
	for  (i = 0; i < input1->getHeight(); i++){
        for (j = 0; j < input1->getWidth(); j++){
        	redCount += input1->getPixel()[3*(i*(input1->getWidth())+j)];
        	greenCount += input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
        	blueCount += input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
        }     
    }
	
	fprintf(f_out2, "CHECKSUM: %d, %d, %d\n", redCount, greenCount, blueCount);
	fclose(f_out2);

};

void CheckSum::Execute()
{
	//Do nothing
};

void CheckSum::Update()
{
	//Do nothing
};

const char* Shrinker::filterName()
{
	return ("Shrinker");
};

void Shrinker::Execute()
{
	//set the image height and width
	img.SetSize(input1->getWidth()/2, input1->getHeight()/2);
    
    int i, j;
    for  (i = 0; i < img.getHeight(); i++){
        for (j = 0; j < img.getWidth(); j++){
        	//set the output pixel data equal to i*2 and j*2
            img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*((i*2)*(input1->getWidth())+(j*2))];
            img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*((i*2)*(input1->getWidth())+(j*2))+1];
            img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*((i*2)*(input1->getWidth())+(j*2))+2];
        }
    }
};

const char* LRConcat::filterName()
{
	return ("LRConcat");
};

void LRConcat::Execute()
{   
    if (input1 == NULL){
    	char msg[1024];
    	sprintf(msg, "%s: no input1!", sinkName());
		DataFlowException e(sinkName(), msg);
		throw e;
    }
    if (input2 == NULL){
    	//execution test #2
    	char msg[1024];
    	sprintf(msg, "%s: no input2!", sinkName());
		DataFlowException e(sinkName(), msg);
		throw e;
    }
    //left input = input, right input = input2
	//set the image height and width
    img.SetSize(input1->getWidth()+input2->getWidth(), input1->getHeight());
    
    if (input1->getHeight() != input2->getHeight()){
    	//exception test #1
    	char msg[1024];
		sprintf(msg, "%s: heights must match: %d, %d", sinkName(), input1->getHeight(), input2->getHeight());
		DataFlowException e(sinkName(), msg);
		throw e;
    } else {
    	int i, j;
    	for  (i = 0; i < img.getHeight(); i++){
        	for (j = 0; j < input1->getWidth(); j++){
        		//set the output pixel data for the left half of total width
            	img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)];
            	img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
            	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
        	}
    	}
    	for  (i = 0; i < img.getHeight(); i++){
        	for (j = 0; j < input2->getWidth(); j++){
        		//set the output pixel data for right hald of total width using an offset (equal to leftInput.width)
            	img.getPixel()[3*(i*(img.getWidth())+j+input1->getWidth())] = input2->getPixel()[3*(i*(input2->getWidth())+j)];
            	img.getPixel()[3*(i*(img.getWidth())+j+input1->getWidth())+1] = input2->getPixel()[3*(i*(input2->getWidth())+j)+1];
            	img.getPixel()[3*(i*(img.getWidth())+j+input1->getWidth())+2] = input2->getPixel()[3*(i*(input2->getWidth())+j)+2];
        	}
   		} 

    }
    
     
};

const char* TBConcat::filterName()
{
	return ("TBConcat");
};

void TBConcat::Execute()
{
	//top input = input, bottom input = input2
	//set the image height and width
    img.SetSize(input1->getWidth(), input1->getHeight()+input2->getHeight());
    
    if (input1->getWidth() != input2->getWidth()) {
		char msg[1024];
		sprintf(msg, "%s: widths must match: %d, %d", sinkName(), input1->getWidth(), input2->getWidth());
		DataFlowException e(sinkName(), msg);
		throw e; 
	}

    int i, j;
    for  (i = 0; i < input1->getHeight(); i++){
        for (j = 0; j < img.getWidth(); j++){
        	//set the output pixel data for the top half of image
            img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(img.getWidth())+j)];
            img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(img.getWidth())+j)+1];
            img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(img.getWidth())+j)+2];
        }
    }
    for  (i = 0; i < input2->getHeight(); i++){
        for (j = 0; j < img.getWidth(); j++){
        	//set the output pixel data for the bottom half using offset (topInput.height)
            img.getPixel()[3*((i+input1->getHeight())*(img.getWidth())+j)] = input2->getPixel()[3*(i*(input2->getWidth())+j)];
            img.getPixel()[3*((i+input1->getHeight())*(img.getWidth())+j)+1] = input2->getPixel()[3*(i*(input2->getWidth())+j)+1];
            img.getPixel()[3*((i+input1->getHeight())*(img.getWidth())+j)+2] = input2->getPixel()[3*(i*(input2->getWidth())+j)+2];
        }
    }
};

const char* Blender::filterName()
{
	return ("Blender");
};

void Blender::Execute()
{
	//input1 = input, input2 = input2
	//set the image height and width
    img.SetSize(input1->getWidth(), input1->getHeight());
    
    if (factor > 1.0){
    	//exception test #3
    	char msg[1024];
		sprintf(msg, "%s: Invlaid factor for Blender: %f", sinkName(), factor);
		DataFlowException e(sinkName(), msg);
		throw e; 
    }
    
    int i, j;
    for  (i = 0; i < img.getHeight(); i++){
        for (j = 0; j < img.getWidth(); j++){
        	//set the output pixel data equal to V1*factor + V2*(1-factor)
            img.getPixel()[3*(i*(img.getWidth())+j)] = (input1->getPixel()[3*(i*(input1->getWidth())+j)] * factor) + input2->getPixel()[3*(i*(input2->getWidth())+j)] * (1-factor);
            img.getPixel()[3*(i*(img.getWidth())+j)+1] = (input1->getPixel()[3*(i*(input1->getWidth())+j)+1] * factor) + input2->getPixel()[3*(i*(input2->getWidth())+j)+1] * (1-factor);
            img.getPixel()[3*(i*(img.getWidth())+j)+2] = (input1->getPixel()[3*(i*(input1->getWidth())+j)+2] * factor) + input2->getPixel()[3*(i*(input2->getWidth())+j)+2] * (1-factor);
        }
    }
};

void Blender::SetFactor(float fctr)
{
	factor = fctr;
};

//new filters

const char* Mirror::filterName()
{
	return ("Mirror");
};

void Mirror::Execute()
{ 
	//mirror image
	img.SetSize(input1->getWidth(), input1->getHeight());
	
	int i, j;
    for  (i = 0; i < input1->getHeight(); i++){
        for (j = 0; j < input1->getWidth(); j++){
        	img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+(input1->getWidth()-j-1))];
        	img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+(input1->getWidth()-j-1))+1];
        	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+(input1->getWidth()-j-1))+2];
        }
    }
};

const char* Rotate::filterName()
{
	return ("Rotate");
};

void Rotate::Execute()
{ 
	//top row of input will equal right most column of output
	img.SetSize(input1->getHeight(), input1->getWidth());
	
	
	int i, j;
    for  (i = 0; i < input1->getWidth(); i++){
        for (j = 0; j < input1->getHeight(); j++){
        	img.getPixel()[3*(i*(img.getWidth())+(img.getWidth()-j-1))] = input1->getPixel()[3*(j*(input1->getWidth())+i)];
        	img.getPixel()[3*(i*(img.getWidth())+(img.getWidth()-j-1))+1] = input1->getPixel()[3*(j*(input1->getWidth())+i)+1];
        	img.getPixel()[3*(i*(img.getWidth())+(img.getWidth()-j-1))+2] = input1->getPixel()[3*(j*(input1->getWidth())+i)+2];
        }
    }
};

const char* Subtract::filterName()
{
	return ("Subtract");
};

void Subtract::Execute()
{ 	
	//check to make sure heights and widths do not match
	if (input1->getWidth() != input2->getWidth()){
		char msg[1024];
		sprintf(msg, "%s: Input widths do not match: %d != %d", sinkName(), input1->getWidth(), input2->getWidth());
		DataFlowException e(sinkName(), msg);
		throw e;
	}
	if (input1->getHeight() != input2->getHeight()){
		char msg[1024];
		sprintf(msg, "%s: Input heights do not match: %d != %d", sinkName(), input1->getHeight(), input2->getHeight());
		DataFlowException e(sinkName(), msg);
		throw e;
	} else {
		img.SetSize(input1->getWidth(), input1->getHeight());
	
		int i, j;
		//apply subtraction
    	for  (i = 0; i < input1->getHeight(); i++){
        	for (j = 0; j < input1->getWidth(); j++){
        		if (input1->getPixel()[3*(i*(img.getWidth())+j)] > input2->getPixel()[3*(i*(input2->getWidth())+j)]){
        			img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)] - input2->getPixel()[3*(i*(input2->getWidth())+j)];
        		} else {
        			img.getPixel()[3*(i*(img.getWidth())+j)] = 0;
        		}
        		if (input1->getPixel()[3*(i*(img.getWidth())+j)+1] > input2->getPixel()[3*(i*(input2->getWidth())+j)+1]){
        			img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1] - input2->getPixel()[3*(i*(input2->getWidth())+j)+1];
        		} else {
        			img.getPixel()[3*(i*(img.getWidth())+j)+1] = 0;
        		}
        		if (input1->getPixel()[3*(i*(img.getWidth())+j)+2] > input2->getPixel()[3*(i*(input2->getWidth())+j)+2]){
        			img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2] - input2->getPixel()[3*(i*(input2->getWidth())+j)+2];
        		} else {
        			img.getPixel()[3*(i*(img.getWidth())+j)+2] = 0;
        		}
        	}
    	}
	}
};

const char* Grayscale::filterName()
{
	return ("Grayscale");
};

void Grayscale::Execute()
{ 
	//apply formula to each color channel
	img.SetSize(input1->getWidth(), input1->getHeight());
	int i, j;
    for  (i = 0; i < img.getHeight(); i++){
        for (j = 0; j < img.getWidth(); j++){
        	//set the output pixel data equal to V1*factor + V2*(1-factor)
            img.getPixel()[3*(i*(img.getWidth())+j)] = (input1->getPixel()[3*(i*(input1->getWidth())+j)]/5) + (input1->getPixel()[3*(i*(input1->getWidth())+j)+1]/2) + (input1->getPixel()[3*(i*(input1->getWidth())+j)+2]/4);
    		img.getPixel()[3*(i*(img.getWidth())+j)+1] = (input1->getPixel()[3*(i*(input1->getWidth())+j)]/5) + (input1->getPixel()[3*(i*(input1->getWidth())+j)+1]/2) + (input1->getPixel()[3*(i*(input1->getWidth())+j)+2]/4);
    		img.getPixel()[3*(i*(img.getWidth())+j)+2] = (input1->getPixel()[3*(i*(input1->getWidth())+j)]/5) + (input1->getPixel()[3*(i*(input1->getWidth())+j)+1]/2) + (input1->getPixel()[3*(i*(input1->getWidth())+j)+2]/4);
    	}
	}
};

const char* Blur::filterName()
{
	return ("Blur");
};

void Blur::Execute()
{
    
	img.SetSize(input1->getWidth(), input1->getHeight());
	
	int i, j;
   
   	//loops for the border of image
	for  (i = 0; i < img.getHeight(); i++){ //column
        for (j = 0; j < img.getWidth(); j++){ //row
            	if (i == 0 && j == 0){
            		img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)];
             		img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
	             	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
            	}
        		if (i == 0 && j != 0){
        			img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)];
             		img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
	             	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
        		}
        		if (j == 0 && i != 0){
        			img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)];
             		img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
	             	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
        		}
        		if (j == img.getWidth()-1 && i == img.getHeight()-1){
        			img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)];
             		img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
	             	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
        		} 
        		if (i == img.getHeight()-1 && j != img.getWidth()-1){
        			img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)];
             		img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
	             	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
        		}
        		if (j == img.getWidth()-1 && i != img.getHeight()-1){
        			img.getPixel()[3*(i*(img.getWidth())+j)] = input1->getPixel()[3*(i*(input1->getWidth())+j)];
             		img.getPixel()[3*(i*(img.getWidth())+j)+1] = input1->getPixel()[3*(i*(input1->getWidth())+j)+1];
	             	img.getPixel()[3*(i*(img.getWidth())+j)+2] = input1->getPixel()[3*(i*(input1->getWidth())+j)+2];
        		} 
        	}
        }
        //loop for inside of image, part to be blurred
        for  (i = 1; i < img.getHeight()-1; i++){ //column
        	for (j = 1; j < img.getWidth()-1; j++){ //row
        			img.getPixel()[3*(i*(img.getWidth())+j)] = ((input1->getPixel()[3*((i-1)*(input1->getWidth())+(j-1))]/8) + //input(i-1, j-1)/8
        												   	   (input1->getPixel()[3*(i*(input1->getWidth())+(j-1))]/8) + //input(i, j-1)/8
        												   	   (input1->getPixel()[3*((i+1)*(input1->getWidth())+(j-1))]/8) + //input(i+1, j-1)/8
        												   	   (input1->getPixel()[3*((i-1)*(input1->getWidth())+j)]/8) + //input(i-1, j)/8
        												       (input1->getPixel()[3*((i+1)*(input1->getWidth())+j)]/8) + //input(i+1, j)/8
        												       (input1->getPixel()[3*((i-1)*(input1->getWidth())+(j+1))]/8) + //input(i-1, j+1)/8
        											           (input1->getPixel()[3*(i*(input1->getWidth())+(j+1))]/8) + //input(i, j+1)/8
        											           (input1->getPixel()[3*((i+1)*(input1->getWidth())+(j+1))]/8)); //input(i+1, j+1)
        											   
    				img.getPixel()[3*(i*(img.getWidth())+j)+1] = ((input1->getPixel()[3*((i-1)*(input1->getWidth())+(j-1))+1]/8) + //input(i-1, j-1)/8
    															 (input1->getPixel()[3*(i*(input1->getWidth())+(j-1))+1]/8) + //input(i, j-1)/8
    														 	 (input1->getPixel()[3*((i+1)*(input1->getWidth())+(j-1))+1]/8) + //input(i+1, j-1)/8
        											        	 (input1->getPixel()[3*((i-1)*(input1->getWidth())+j)+1]/8) + //input(i-1, j)/8
        											        	 (input1->getPixel()[3*((i+1)*(input1->getWidth())+j)+1]/8) + //input(i+1, j)/8
        											        	 (input1->getPixel()[3*((i-1)*(input1->getWidth())+(j+1))+1]/8) + //input(i-1, j+1)/8
        											        	 (input1->getPixel()[3*(i*(input1->getWidth())+(j+1))+1]/8) + //input(i, j+1)/8
        											        	 (input1->getPixel()[3*((i+1)*(input1->getWidth())+(j+1))+1]/8)); //input(i+1, j+1)
        											   
    				img.getPixel()[3*(i*(img.getWidth())+j)+2] = ((input1->getPixel()[3*((i-1)*(input1->getWidth())+(j-1))+2]/8) + //input(i-1, j-1)/8
    														 	 (input1->getPixel()[3*(i*(input1->getWidth())+(j-1))+2]/8) + //input(i, j-1)/8
    														 	 (input1->getPixel()[3*((i+1)*(input1->getWidth())+(j-1))+2]/8) + //input(i+1, j-1)/8
        											   		 	 (input1->getPixel()[3*((i-1)*(input1->getWidth())+j)+2]/8) + //input(i-1, j)/8
        											   		  	 (input1->getPixel()[3*((i+1)*(input1->getWidth())+j)+2]/8) + //input(i+1, j)/8
        											   		 	 (input1->getPixel()[3*((i-1)*(input1->getWidth())+(j+1))+2]/8) + //input(i-1, j+1)/8
        											   		 	 (input1->getPixel()[3*(i*(input1->getWidth())+(j+1))+2]/8) + //input(i, j+1)/8
        											   		 	 (input1->getPixel()[3*((i+1)*(input1->getWidth())+(j+1))+2]/8)); //input(i+1, j+1)
        		}
        	}
};

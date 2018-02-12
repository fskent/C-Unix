//  logging.C
//
//  Created by Steve Kent on 5/27/17.
//
#include "logging.h"
#include <exception>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
using std::exception;

DataFlowException::DataFlowException(const char *type, const char *error)
{
	//string print to msg
	sprintf(msg, "Throwing Exception: (%s): %s", type, error);
	//log the event
	Logger::LogEvent(msg);	
};

//open the logger file
ofstream Logger::logger("logging.txt");

void Logger::LogEvent(const char *event)
{
	//add the event to logger file, endl provides newline character
	//using cpp file i/o made newline character implementation simpler. 
	logger << event << endl;
};

void Logger::Finalize()
{
	//close the logger file
	logger.close();
};

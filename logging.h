//  logging.h
//
//  Created by Steve Kent on 5/27/17.
//
#ifndef  LOGGING_H
#define  LOGGING_H

#include <exception>
#include <stdio.h>
#include <iostream>
#include <fstream>
using std::exception;
using std::ofstream;


class DataFlowException : public exception
{
  public:
                         DataFlowException(const char *type, const char *error);
    virtual const char  *what() const throw() { return msg; };

  protected:
    char        msg[1024];
};


class Logger
{
  public:
    static void     LogEvent(const char *event);
    static void     Finalize();

  private:
    static   ofstream logger;
};

#endif

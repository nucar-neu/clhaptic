#ifndef __LOGGER__
#define __LOGGER__

#include "stdio.h"

#define ENABLE_WARNINGS

#define ENABLE_LOGGING

class logger
{
private:
	char * filename;
public:
	void add(char * );

};

void print_warning(char * input);

void print_logging(char * input);

#endif // __LOGGER__


#include <iostream>
#include <vector>

#include "logger.h"

void logger::add(char * s)
{
   printf("%s\n",s);
}

//TODO Add File writing options for warnings
void print_warning(char * input_string)
{

#ifdef ENABLE_WARNINGS

	printf("WARNING  - \t");
	printf("%s",input_string);

#endif
}


//TODO Add File writing options for LOGS
void print_logging(char * input_string)
{

#ifdef ENABLE_LOGGING

	printf("LOG  - \t");
	printf("%s",input_string);

#endif
}

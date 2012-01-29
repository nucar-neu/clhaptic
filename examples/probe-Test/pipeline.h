#include <iostream>
#include "stdio.h"

#define MAX_COUNT 3

/*
 *
 * http://stackoverflow.com/questions/412344/a-better-way-than-casting-from-a-base-class-to-derived-class
 *
  Base * bases[NUM_ITEMS];
	for(int i=0; i<NUM_ITEMS; i++) {
    int r = get_random_integer();
    if(r == 0)
        bases[i] = new Derived1;
    else if(r == 1)
        bases[i] = new Derived2;
    // ...
}
 *
 */
class base_device;

class base_device
{
public:
	virtual ~base_device()
	{
		printf("base destructor\n");
	}

	int position;
	int device_name;

	void run();
	virtual void configure_device(int i)
	{
		printf("Wrong func called\n");
	}
};


class test_device_0: public base_device
{
public:
	~test_device_0(){}
	void configure_device(int i)
	{
		printf("Setup - device 0 - Implementation\n");
		position = i;
		device_name = 0;
	}
	void random_device_0_crap()
	{
	    printf("Doing something specific for device 0\n");
	}
};

class test_device_1: public base_device
{
public:
	~test_device_1(){}
	void configure_device(int i)
	{
		printf("Setup - device 1 - Implementation\n");
		position = i;
		device_name = 1;
	}
};

class test_device_2: public base_device
{
public:
	~test_device_2(){}
	void configure_device(int i)
	{
		printf("Setup - device 2 - Implementation\n");
		position = i;
		device_name = 2;
	}
};

class compute_pipeline
{
public:
	base_device * devices[MAX_COUNT];
	void run();

};

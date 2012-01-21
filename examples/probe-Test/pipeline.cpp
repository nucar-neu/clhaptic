#include "pipeline.h"



void base_device::run()
{
	printf("Running device\t NAME %d\t Position\t %d \n",device_name,position);

}

/*void base_device::~base_device()
{
	printf("\nBase Class Destructor\n\n");

}
*/

void compute_pipeline::run()
{
	printf("\nPIPELINE STAGE 0 \n");
	devices[0]->run();
	printf("\nPIPELINE STAGE 1 \n\n");
	devices[1]->run();
	printf("\nPIPELINE STAGE 2 \n\n");
	devices[2]->run();
	printf("\nEND PIPELINE \n\n");
}

int main(int argc, char ** argv)
{
	compute_pipeline * some_pipe = new compute_pipeline[1];
	some_pipe->devices[0] = new test_device_0[1];
	some_pipe->devices[0]->configure_device(0);

	some_pipe->devices[1] = new test_device_1[1];
	some_pipe->devices[1]->configure_device(1);

	some_pipe->devices[2] = new test_device_2[1];
	some_pipe->devices[2]->configure_device(2);

	some_pipe->run();
}

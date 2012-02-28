#include "kernel-object.h"

kernel_object alloc_kernel_object()
{
	return new _kernel_object;
}

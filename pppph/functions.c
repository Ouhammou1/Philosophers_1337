#include "philo.h"

void	printf_error(char 	*str)
{
	printf("%s\n", str);
	exit(1);
}
void 	*save_memory(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if(!ptr)
		printf_error("Malloc failed");
	return (ptr);
}
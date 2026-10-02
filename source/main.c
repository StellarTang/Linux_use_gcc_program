#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "onedirectional_linked_list.h"
#include "bidirectional_linked_list.h"



void test_getopt(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "r:m:o:h")) != -1)
	{
		switch (opt)
		{
			case 'r':
				printf("Option -r with value: %s\n", optarg);
				break;	
			case 'm':
				printf("Option -m with value: %s\n", optarg);
				break;
			case 'o':
				printf("Option -o with value: %s\n", optarg);
				break;
			case 'h':
				printf("Option -h (help) selected\n");
				break;
			default:
				fprintf(stderr, "Usage: %s [-r value] [-m value] [-o value] [-h]\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
}


void test_argc_argv(int argc, char *argv[])
{
	printf("argc = %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
}

int main(int argc, char *argv[])
{

	test_argc_argv(argc, argv);
	test_getopt(argc, argv);

	test_onedirectional_linked_list();
	test_bidirectional_linked_list();

	return 0;
}




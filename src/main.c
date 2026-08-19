#include <stdio.h>
#include <stdlib.h>

#include "string_util.h"

int main (int argc, char** argv){
	string_t arr;
	string_new(&arr, 0);
	string_push(&arr, "Hwllo", 5);
	string_push(&arr, "Hellooi0\n", 10);
	string_push(&arr, "something random", 16);
	prints(arr.content, arr.size);
	printf("%d\n", arr.size);
	
	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <string.h>
#include "dict.h"

int main(int argc, char const *argv[])
{
	Dict myDict = dict();

	addNode(&myDict, NULL, NULL);

	printDict(myDict);
	destroyDict(myDict);
	return 0;
}
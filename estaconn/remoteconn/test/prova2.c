#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;

	fp = (FILE *) popen( "ssh -l tinmr305 localhost", "r");

	return (0);
}

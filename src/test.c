#include <stdio.h>
#include <stdlib.h>

int main() {

	for(int k = 0; k < 20 ; k ++){
		printf("value : %d\n", -k%3);
	}

	return 0;
}
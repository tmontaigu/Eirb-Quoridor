#include <stdio.h>
#include <assert.h>

#include "../src/headers/structQuoridor.h"

int main(int argc, char **argv) {
	int column = 1;
	int row = 1;
	
	int direction = 66;
	
	printf("Begining tests of determine_direction\n");
	
	direction = determine_direction(column,row,column+1,row);
	assert(direction == right);
	direction = determine_direction(column,row,column-1,row);
	assert(direction == left);
	direction = determine_direction(column,row,column,row-1);
	assert(direction == up);
	direction = determine_direction(column,row,column,row+1);
	assert(direction == down);
	
	direction = determine_direction(column,row,column+2,row);
	assert(direction == invalid);
	
	printf("All tests done\n");
}

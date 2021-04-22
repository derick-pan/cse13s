#include <stdbool.h>
#include <stdint.h>
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
typedef uint32_t Set;
#define SET_CAPACITY 32 // 32 bits means 32 items max.

Set set_empty(void){//return an empty set
	uint32_t s = 0;
	return s;

	}
bool set_member(Set s, int x){//True if x in set
	uint32_t y = (uint32_t) (int) x;
//	printf("\nset: %u x: %u\n", s, y);


	return ((s & y) == y);
	}	
Set set_insert(Set s, int x){ 
	s = (s | x);
//	printf("Set_insert: %u\n", s);
//	printf("Set after insert:  %u \n",s); 
	return s;
}
Set set_remove(Set s, int x);
	
Set set_union(Set s, Set t);

Set set_intersect(Set s, Set t);

Set set_difference(Set s, Set t);

Set set_complement(Set s);

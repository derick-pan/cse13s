//Derick Pan
//dpan7
//Asgn5
//Encode.c
#include "bm.h"
#include "bv.h"


#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>





int main(){
for (uint8_t k =0; k < 4; k++){
    bm_set_bit(m, k, k);
}
for (uint8_t j = 0; j < 4; j++){
    for (uint8_t j = 4; j < 8; j++){
        bm_set_bit(m, i, j);
}
for (uint8_t i =4; i < 8; i++){
    bm_clr_bit(m, i, i);
}
}

#include <stdlib.h>
#include <stdbool.h>
#include "./ivec_ext.h"
#include <assert.h>


void ivec_filter(IntVec* xs, bool (*f)(int)) {
       assert(xs != NULL);
       int i = ivec_length(xs);
       while(i > 0 ){
             --i;
             if(!f(*ivec_at(xs, i))){
               ivec_remove(xs, i);
             }
       }
}
/* helper function */
int sum(int x, int y){
     return x + y;
}

int product(int x, int y){
     return x*y;
}

int ivec_fold(IntVec* xs, int y, int (*f)(int, int)) {
    assert(xs != NULL);
    if (ivec_length(xs) == 0){
        return y;
    }
    int result = 0;
    for(int i = 0; i < ivec_length(xs); i++){
        result = f(y, *ivec_at(xs, i));
        y = result;
    }
    return result;
}

int ivec_sum(IntVec* xs) {
    return ivec_fold(xs, 0, sum);
}

int ivec_product(IntVec* xs) {
    return ivec_fold(xs, 1, product);
}



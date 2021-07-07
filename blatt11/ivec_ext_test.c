#include "../unity/unity.h"

#include "./ivec.h"
#include "./ivec_ext.h"

#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}
/* Return True if x is odd */

bool is_odd(int x){
    if(x % 2 != 0){
        return true;
    }
    return false;
}

bool is_even(int x){
    if(x % 2 == 0){
        return true;
    }
    return false;
}
void test_int_vec_filter(void){
    
    IntVec* vec = ivec_new();
    for(int i=1; i<=20; i++ ){
        ivec_push(vec, i);
    }
    /* Initially The total element numver is equal to the number of added
     * elements
     */
    TEST_ASSERT_EQUAL_size_t(20, ivec_length(vec));
    
    ivec_filter(vec, &is_even);
    /* After all the even elements are filtered all the odd elemnts will ber
     * removed, hence the elements left must be all even */
    for(int i=0; i < ivec_length(vec); i++ ){
        TEST_ASSERT_EQUAL_INT((i + 1) * 2, *ivec_at(vec, i));
    }
    TEST_ASSERT_EQUAL_size_t(10, ivec_length(vec));
    /* Again all the even elements will be filtered out. Hence the field is
     * empty
     */
    ivec_filter(vec, &is_odd);
    TEST_ASSERT_EQUAL_size_t(0, ivec_length(vec));

    ivec_free(vec);

}

void test_ivec_sum(void){
     IntVec* xs = ivec_new();
     for(int i=1; i < 11; i++){
        ivec_push(xs, i);
     }
     /*The sum of first 10 natural numbers is 55*/
     TEST_ASSERT_EQUAL_INT(55, ivec_sum(xs));
     /* The sum of first 9 natural numbers is 45*/
     ivec_pop(xs);
     TEST_ASSERT_EQUAL_INT(45, ivec_sum(xs));
     ivec_free(xs);
}

void test_ivec_product(void){
     IntVec* xs = ivec_new();
     for(int i=1; i < 11; i++){
        ivec_push(xs, i);
     }
     /* Since the elemnts are natural number from 1 - 10, the product of those
      * numbers is same as factorial of 10 */
     TEST_ASSERT_EQUAL_INT(3628800, ivec_product(xs));
     ivec_pop(xs);
     TEST_ASSERT_EQUAL_INT(362880, ivec_product(xs));
     ivec_push(xs, 0);
     /* If there exist atleast one zero the product must be zero */
     TEST_ASSERT_EQUAL_INT(0, ivec_product(xs));
     ivec_free(xs);
}
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_int_vec_filter);
  RUN_TEST(test_ivec_sum);
  RUN_TEST(test_ivec_product);
  return UNITY_END();
}

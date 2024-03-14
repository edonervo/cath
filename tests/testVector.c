#include "unity.h"
#include "Vector.h"
#include <stdlib.h>
#include <stdio.h>     


void setUp(){
    /*
    The setUp function can contain anything
    you would like to run before each test.
    */ 
   }

void tearDown(){
    /*
    The tearDown function can contain anything 
    you would like to run after each test
    */ 
   }

void test_vector_init() {
    Vector vector;
    size_t size = 10;
    initVector(&vector, size);
    // printf("%p", vector.data);
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, 0.0, vector.data[0]);
    // freeVector(&vector);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_vector_init);

    UNITY_END();

    return EXIT_SUCCESS;
}

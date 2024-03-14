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

int main(void) {
    UNITY_BEGIN();

    puts("Hello Test!");

    UNITY_END();

    return EXIT_SUCCESS;
}

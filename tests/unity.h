#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>
#include <stdlib.h>

#define TEST_ASSERT_EQUAL_INT(expected, actual) \
    if ((expected) != (actual)) { \
        printf("Test failed: expected %d but got %d\n", (expected), (actual)); \
        exit(1); \
    }

#define TEST_ASSERT_TRUE(condition) \
    if (!(condition)) { \
        printf("Test failed: condition is false\n"); \
        exit(1); \
    }

void run_tests(void);

#endif // UNITY_H
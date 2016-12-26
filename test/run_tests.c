#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>

extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);

#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)

char * stringreturner(){
    return "teststring";
}

void leak_memory(){
    int * allocated_but_not_freed;
    *(allocated_but_not_freed) = 1;
}

void badalloc(){
    int *array = (int *)malloc(sizeof(int)*40);
}

void goodalloc(){
    int *array = (int *)malloc(sizeof(int)*40);
    free(array);
}

//Testing datatypes
void test_string_pass(void **state) {
    assert_string_equal(stringreturner(), "teststring");
}

void test_string_fail(void **state) {
    assert_string_equal(stringreturner(), "anotherstring");
}

//Testing memory leaks
void test_memory_leak(void **state){
    leak_memory();
}

void test_memory_leak2(void **state){
    badalloc();
}

void test_memory_leak3(void **state){
    goodalloc();
}

int main(int argc, char* argv[]) {
    const struct CMUnitTest test_suit[] = {
        cmocka_unit_test(test_string_pass),
        cmocka_unit_test(test_string_fail),
        cmocka_unit_test(test_memory_leak),
        cmocka_unit_test(test_memory_leak2),
        cmocka_unit_test(test_memory_leak3)
    };
    return cmocka_run_group_tests(test_suit, NULL, NULL);
}

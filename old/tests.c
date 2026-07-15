#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "my_str.h"

int main() {
    
    /*##########################################################
    #                     tests for MyStr                      #
    ##########################################################*/

    printf("\033[34m");

    // constructor tests:
    MyStr s1 = new_str("Hello");
    MyStr s2 = new_str("");
    assert(s1 != NULL);
    assert(s2 != NULL);
    assert(s1->capacity == DEFAULT_CAPACITY);
    assert(s2->capacity == DEFAULT_CAPACITY);
    assert(s1->str != NULL);
    assert(s2->str != NULL);
    assert(s1->size == strlen("Hello"));
    assert(s2->size == 0);
    printf("\033[36mconstructor tests past\033[34m\n\n");

    // push char tests:
    push_char(s1, ',');
    assert(s1->size == strlen("Hello,"));
    printf("\033[36mpush char tests past\033[34m\n\n");
    push_str(s2, " World! This text is AI generated and explicitly states its artificial origin for clarity and transparency. It was produced by an AI system. Clearly.!");
    assert(s2->capacity > DEFAULT_CAPACITY);
    printf("resize succesfull\n");
    assert(s2->size == 150);
    printf("\033[36mpush str tests past\033[34m\n\n");

    // get str test:
    const char* cmp1 = "Hello,";
    const char* result = get_str(s1);
    assert(strlen(result) == strlen(cmp1));
    for (int i = 0; i < strlen(cmp1); i++) {
        assert(result[i] == cmp1[i]);
    }
    printf("\033[36mget str tests past\033[34m\n\n");

    // pop test:
    char poped = pop_back(s2);
    assert(poped == '!');
    assert(s2->size == 149);
    printf("\033[36mpop tests past\033[34m\n\n");

    // append tests:
    append(s1, s2);
    assert(s1->capacity > DEFAULT_CAPACITY);
    assert(s1->size == 149 + strlen("Hello,"));
    const char* cmp2 = "Hello, World! This text is AI generated and explicitly states its artificial origin for clarity and transparency. It was produced by an AI system. Clearly.";
    assert(strlen(get_str(s1)) == strlen(cmp2));
    for (int i = 0; i < strlen(cmp2); i++) {
        assert(s1->str[i] == cmp2[i]);
    }
    printf("\033[36mappend tests past\033[34m\n\n");

    // clear tests:
    clear(s2);
    assert(s2->size == 0);
    assert(strlen(get_str(s2)) == 0);
    assert(s1->size == 149 + strlen("Hello,"));         // changes on s2 should have no effect on s1
    push_char(s2, '!');
    assert(s2->size == 1);
    printf("\033[36mclear tests past\033[34m\n\n");

    // destryer tests:
    destroy(s1);
    destroy(s2);
    s1 = NULL;
    s2 = NULL;
    printf("\033[36mdestroyer tests past\033[34m\n\n");

    return 0;
}

#include "my_str.h"

/*##########################################################
#                         functions                        #
##########################################################*/

MyStr new_str(const char* str) {
    MyStr self = malloc(sizeof(struct MyStr));
    if (self == NULL) {
        return NULL;
    }

    self->capacity = DEFAULT_CAPACITY;
    self->size = 0;

    self->str = malloc(self->capacity * sizeof(char));
    if (self->str == NULL) {
        free(self);
        return NULL;
    }

    if (str == "" || str == NULL) {
        self->str[0] = '\0';
    } else {
        push_str(self, str);
    }

    return self;
}

int resize(MyStr self, size_t new_size) {
    if (self == NULL) {
        return 0;
    }

    char* reallocated = realloc(self->str, new_size * sizeof(char));
    if (reallocated == NULL) {
        return 0;
    }

    self->capacity = new_size;
    self->str = reallocated;
    return 1;
}

void push_char(MyStr self, char ch) {
    if (self == NULL || ch == END_OF_STR) {
        return;
    }
    
    if (self->size == self->capacity) {
        if (!resize(self, self->capacity * 2)) {
            return;
        }
    }

    self->str[self->size++] = ch;
    self->str[self->size] = END_OF_STR;
}

void push_str(MyStr self, const char* str) {
    if (self == NULL || str == NULL) {
        return;
    }

    for (size_t i = 0; str[i] != END_OF_STR; i++) {
        push_char(self, str[i]);
    }
}

const char* get_str(MyStr self) {
    if (self == NULL) {
        return NULL;
    }

    return (const char*)self->str;
}

char pop_back(MyStr self) {
    if (self == NULL || self->size == 0) {
        return END_OF_STR;
    }

    self->size -= 1;
    char last_char = self->str[self->size];
    self->str[self->size] = END_OF_STR;
    return last_char;
}

int clear(MyStr self) {
    if (self == NULL || self->str == NULL) {
        return 0;
    }

    self->size = 0;
    self->str[0] = END_OF_STR;
    return 1;
}

int append(MyStr self, MyStr source) {
    if (self == NULL || self->str == NULL || source == NULL || source->str == NULL) {
        return 0;
    }

    if (self->size + source->size >= self->capacity) {
        if (!resize(self, self->capacity + source->size)) {
            return 0;
        }
    }

    size_t large_chunks_count = source->size / LARGE_CHUNK_SIZE;
    size_t small_chunks_count = source->size % LARGE_CHUNK_SIZE;

    uint64_t* src_large_ptr = (uint64_t*)source->str;
    uint64_t* dst_large_ptr = (uint64_t*)(self->str + self->size);

    for (size_t i = 0; i < large_chunks_count; i++) {
        dst_large_ptr[i] = src_large_ptr[i];
        self->size += LARGE_CHUNK_SIZE;
    }

    uint8_t* src_small_ptr = (uint8_t*)(src_large_ptr + large_chunks_count);
    uint8_t* dst_small_ptr = (uint8_t*)(dst_large_ptr + large_chunks_count);

    for (size_t i = 0; i < small_chunks_count; i++) {
        dst_small_ptr[i] = src_small_ptr[i];
        self->size += 1;
    }

    self->str[self->size] = END_OF_STR;
    
    return 1;
}

void destroy(MyStr self) {
    if (self == NULL) {
        return;
    }

    if (self->str != NULL) {
        free(self->str);
        self->str == NULL;
    }
    free(self);
    self = NULL;
}
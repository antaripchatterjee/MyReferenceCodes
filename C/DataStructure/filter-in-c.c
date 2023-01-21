#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct filter_t {
        void* dest_data_ptr;
        size_t length;
};


typedef int(*filtering_callback_t)(void*, size_t);

void filter(void* src_data_ptr, size_t src_data_size, size_t src_item_size, struct filter_t *dest, filtering_callback_t callback)
{
        for(size_t index = 0; index < src_data_size; index++) {
                if(callback(src_data_ptr, index)) {
                        dest->dest_data_ptr = dest->dest_data_ptr == NULL ?
                                malloc(src_item_size) :
                                realloc(dest->dest_data_ptr, src_item_size*(dest->length+1));
                        memmove(dest->dest_data_ptr+src_item_size*(dest->length++), src+index*src_item_size, src_item_size);
                }
        }
}

int filter_evens(void* src_data_ptr, size_t index) {
        return ((int*) src_data_ptr)[index] % 2 == 0;
}

int main() {
        int arr[10] = { 9, 3, 2, 0, 5, 6, 4, 8, 1, 7};
        struct filter_t evens = { NULL, 0 };
        filter(arr, sizeof(arr)/sizeof(int),  sizeof(int),  &evens, filter_evens);
        printf("Count: %ld\n", evens.length);
        for(size_t i = 0; i < evens.length; i++) {
                printf("Item %ld -> %d\n", i, ((int*) evens.dest_data_ptr)[i]);
        }
        return 0;
}

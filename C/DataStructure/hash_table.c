#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} pair_t;

typedef struct {
    pair_t* pair_set;
    size_t count;
} hash_row_t;

typedef struct {
    hash_row_t* rows;
    size_t count;
} hash_table_t;


hash_table_t* new_hash_table(size_t count) {
    hash_table_t* table = (hash_table_t*) malloc(sizeof(hash_table_t));
    if(!table) return NULL;
    table->rows = (hash_row_t*) malloc(sizeof(hash_row_t) * count);
    if(!table->rows) {
        free(table);
        return NULL;
    }
    for(size_t i = 0; i < count; i++) {
        (table->rows + i)->pair_set = NULL;
        (table->rows + i)->count = 0;
    }
    table->count = count;
    return table;
}

long int get_hash_index(const char* key, size_t table_size) {
    if(!key) return -1;
    if(table_size <= 0) return -2;
    const int factor_1 = 37 * strlen(key);
    const int factor_2 = 93 * strlen(key);
    unsigned hash_value = 0;
    for(size_t i = 0; i < strlen(key); i++) {
        unsigned ascii = (unsigned) key[i];
        hash_value += factor_1 * ascii + factor_2 * ascii/2;
    }
    return (long int) hash_value % table_size;
}
void free_hash_table(hash_table_t* table) {
    if(!table) return;
    for(size_t row_i = 0; row_i < table->count; row_i++) {
        if(!(table->rows + row_i)) continue;
        for(size_t pair_i = 0; pair_i < (table->rows + row_i)->count; pair_i++) {
            if(!((table->rows + row_i)->pair_set + pair_i)) continue;
            if(((table->rows + row_i)->pair_set + pair_i)->key)
                free(((table->rows + row_i)->pair_set + pair_i)->key);
        }
        free((table->rows + row_i)->pair_set);
    }
    free(table->rows);
    free(table);
    table = NULL;
}

const long int has_hash_key(hash_table_t* table, const char* key, long int hash_value) {
    if(!table) return -2l;
    if(!key) return -1l;
    if(hash_value < 0) hash_value = get_hash_index(key, table->count);

    if(hash_value >= 0)  {
        hash_row_t* row = table->rows + hash_value;
        if(row) {
            for(size_t i = 0; i < row->count && row->pair_set; i++) {
                if((row->pair_set + i)->key) {
                    if(strcmp((row->pair_set + i)->key, key) == 0)
                        return (const long int)i;
                }
            }
        }
    }
    return -3l;
}

void free_hash_keys(char** keys, size_t *keys_len) {
    if(!keys) return;
    if(!keys_len) return;
    while(*keys_len) {
        *keys_len = *keys_len - 1;
        free(keys[*keys_len]);
    }
    free(keys);
    keys = NULL;
}
void free_hash_values(int* values, size_t *values_len) {
    if(!values) return;
    if(!values_len) return;
    *values_len = 0;
    free(values);
    values = NULL;
}

void free_hash_pairs(pair_t* pairs, size_t* pairs_len) {
    if(!pairs) return;
    if(!pairs_len) return;
    while(*pairs_len) {
        *pairs_len = *pairs_len - 1;
        free(pairs[*pairs_len].key);
    }
    free(pairs);
    pairs = NULL;
}
char** get_hash_keys(hash_table_t* table, size_t *keys_len) {
    if(!keys_len) return NULL;
    *keys_len = 0;
    if(!table) return NULL;
    char** keys = NULL;
    for(size_t i = 0; i < table->count && table->rows; i++) {
        hash_row_t* row = (table->rows + i);
        if(!row) continue;
        for(size_t j = 0; j < row->count && row->pair_set; j++) {
            pair_t* pair = (row->pair_set + j);
            if(!pair) continue;
            if(!pair->key) continue;
            if(keys) {
                keys = (char**) realloc(keys, sizeof(char*) * (*keys_len + 1));
            } else {
                keys = (char**) malloc(sizeof(char*));
            }
            if(!keys) {
                *keys_len =0;
                return NULL;
            }
            char* key = (char*) malloc(sizeof(char) * (strlen(pair->key) + 1));
            if(!key) {
                free_hash_keys(keys, keys_len);
                return NULL;
            }
            memset(key, '\0', sizeof(char) * (strlen(pair->key) + 1));
            strcpy(key, pair->key);
            *(keys + *keys_len) = key;
            *keys_len = *keys_len + 1;
        }
    }
    return keys;
}

int* get_hash_values(hash_table_t* table, size_t *values_len) {
    if(!values_len) return NULL;
    *values_len = 0;
    if(!table) return NULL;

    int* values = NULL;
    for(size_t i = 0; i < table->count && table->rows; i++) {
        hash_row_t* row = (table->rows + i);
        if(!row) continue;
        for(size_t j = 0; j < row->count && row->pair_set; j++) {
            pair_t* pair = (row->pair_set + j);
            if(!pair) continue;
            if(!pair->key) continue;
            if(values) {
                values = (int*) realloc(values, sizeof(int) * (*values_len + 1));
            } else {
                values = (int*) malloc(sizeof(int));
            }
            if(!values) {
                *values_len =0;
                return NULL;
            }
            *(values + *values_len) = pair->value;
            *values_len = *values_len + 1;
        }
    }
    return values;
}

pair_t* get_hash_pairs(hash_table_t* table, size_t* pairs_len) {
    if(!pairs_len) return NULL;
    *pairs_len = 0;
    if(!table) return NULL;
    pair_t* pairs = NULL;

    for(size_t i = 0; i < table->count && table->rows; i++) {
        hash_row_t* row = (table->rows + i);
        if(!row) continue;
        for(size_t j = 0; j < row->count && row->pair_set; j++) {
            pair_t* pair = (row->pair_set + j);
            if(!pair) continue;
            if(!pair->key) continue;
            if(pairs) {
                pairs = (pair_t*) realloc(pairs, sizeof(pair_t) * (*pairs_len + 1));
            } else {
                pairs = (pair_t*) malloc(sizeof(pair_t));
            }
            if(!pairs) {
                *pairs_len =0;
                return NULL;
            }
            (pairs + *pairs_len)->key = (char*) malloc(sizeof(char) * (strlen(pair->key) + 1));
            memset((pairs + *pairs_len)->key, '\0', sizeof(char) * (strlen(pair->key) + 1));
            strcpy((pairs + *pairs_len)->key, pair->key);
            (pairs + *pairs_len)->value = pair->value;
            *pairs_len = *pairs_len + 1;
        }
    }
    return pairs;
}

const long int set_hash_item(hash_table_t* table, const char* key, int value) {
    if(!table) return -2l;
    if(!key) return -1l;
    const long int hash_value = get_hash_index(key, table->count);
    if(hash_value < 0) return -3l + hash_value;
    const long int key_index_in_row = has_hash_key(table, key, hash_value);
    hash_row_t* row = (table->rows + hash_value);
    if(key_index_in_row >= 0) {
        (row->pair_set + key_index_in_row)->value = value;
    } else {
        if(row->pair_set) {
            row->pair_set = (pair_t*) realloc(row->pair_set, sizeof(pair_t) * (row->count + 1));
        } else {
            row->pair_set = (pair_t*) malloc(sizeof(pair_t));
        }
        if(!row->pair_set) return -3l;

        (row->pair_set + (row->count))->key = (char*) malloc(sizeof(char) * (strlen(key) + 1));
        if(!(row->pair_set + row->count)->key) return -3;
        memset((row->pair_set + row->count)->key, '\0', sizeof(char) * (strlen(key) + 1));
        strcpy((row->pair_set + row->count)->key, key);
        (row->pair_set + row->count++)->value = value;
    }
    
    return hash_value;
}
const long int get_hash_item(hash_table_t* table, const char* key, int* value) {
    if(!key) return -1l;
    if(!table) return -2l;
    const long int hash_value = get_hash_index(key, table->count);
    if(hash_value < 0) return -3l + hash_value;
    hash_row_t* row = (table->rows + hash_value);
    if(!row) return -3l;
    if(!row->pair_set) return -3l;
    short found = 0;
    for(size_t i = 0; i < row->count && !found; i++) {
        pair_t* pair = (row->pair_set + i * sizeof(pair_t));
        if(pair) {
            if(pair->key) {
                if(strcmp(pair->key, key) == 0) {
                    *value = pair->value;
                    found = 1;
                }
            }
        }
    }
    return found ? hash_value : -3l;
}
int main() {
    hash_table_t* table = new_hash_table(1000);
    printf("Key `a` exist? %s\n", has_hash_key(table, "a", -1) >= 0l ? "yes" : "no");
    printf("Item `a` set at %ld\n", set_hash_item(table, "a", 1));
    printf("Item `b` set at %ld\n", set_hash_item(table, "b", 3));
    printf("Key `a` exist? %s\n", has_hash_key(table, "a", -1) >= 0l ? "yes" : "no");
    int retrieved_value;
    int a_value = get_hash_item(table, "a", &retrieved_value);
    if(a_value >= 0) {
        printf("Item `a` -> %d\n", retrieved_value);
    } else {
        printf("Item `a` could not be found. returned %d\n", a_value);
    }
    const int b_value = get_hash_item(table, "b", &retrieved_value);
    if(b_value >= 0) {
        printf("Item `b` -> %d\n", retrieved_value);
    } else {
        printf("Item `b` could not be found. returned %d\n", b_value);
    }
    printf("Item `a` reset at %ld\n", set_hash_item(table, "a", 15));
    a_value = get_hash_item(table, "a", &retrieved_value);
    if(a_value >= 0) {
        printf("Item `a` -> %d\n", retrieved_value);
    } else {
        printf("Item `a` could not be found. returned %d\n", a_value);
    }
    size_t keys_len = 0;
    char **keys = get_hash_keys(table, &keys_len);
    for(size_t i = 0; i < keys_len; i++) {
        printf("key: %s\n", keys[i]);
    }
    free_hash_keys(keys, &keys_len);
    size_t values_len = 0;
    int* values = get_hash_values(table, &values_len);
    for(size_t i = 0; i < values_len; i++) {
        printf("value: %d\n", values[i]);
    }
    free_hash_values(values, &values_len);

    size_t pairs_len = 0;
    pair_t* pairs = get_hash_pairs(table, &pairs_len);
    for(size_t i = 0; i < pairs_len; i++) {
        printf("pair: %s -> %d\n", pairs[i].key, pairs[i].value);
    }
    free_hash_pairs(pairs, &pairs_len);
    a_value = get_hash_item(table, "a", &retrieved_value);
    if(a_value >= 0) {
        printf("Item `a` -> %d\n", retrieved_value);
    } else {
        printf("Item `a` could not be found. returned %d\n", a_value);
    }
    free_hash_table(table);
    return 0;
}

/***
 * 
 * Compile by: gcc hash_table.c -Wall -std=c11 -o hash_table
 * 
 ***/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"



size_t num_valid_combos_starting_from(const char *s, const int *key, const size_t s_len, const int key_len, int i, int j, size_t *memo){
    if (i>=s_len && j==key_len) return 1;
    if (i >= s_len ) return 0;
    if (j == key_len){
        if (s[i] != '#') return num_valid_combos_starting_from(s, key, s_len, key_len, i+1, j, memo);
        else return 0;
    }
    if (memo[i*key_len + j] != 0) {
        return memo[i*key_len + j];
    }

    size_t res = 0;
    char *next_dot = strchr(s+i, '.');
    int distance_to_next_dot = (next_dot==NULL) ? s_len-i : next_dot - (s + i);
    if (distance_to_next_dot >= key[j] && s[i+key[j]] != '#') res += num_valid_combos_starting_from(s, key, s_len, key_len, i+key[j]+1, j+1, memo);
    if (s[i] == '?' || s[i] == '.') res += num_valid_combos_starting_from(s, key, s_len, key_len, i+1, j, memo);

    memo[i*key_len + j] = res;
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);
    


    size_t total_combos = 0;
    size_t total_combos_part_2 = 0;
    for (int i=0; i<linecount; i++){
        char *s = lines[i];
        char *space = strchr(s, ' ');
        *space = '\0';

        int j = 0;
        char *key_string = space + 1;
        int *key = NULL;
        while (key_string[j] != '\0'){
            int val = extract_number_from_string_starting_from(key_string, &j);
            arrput(key, val);
            if (key_string[j] == ',') j++;
        }
        size_t s_len = strlen(s);
        size_t key_len = arrlen(key);
        size_t *memo = calloc(s_len * key_len, sizeof(size_t));
        total_combos += num_valid_combos_starting_from(s, key, s_len, key_len, 0, 0, memo);



        char *s_part_2 = malloc(s_len*5 + 5);
        char *cursor = s_part_2;
        strcpy(cursor, s);
        cursor += s_len;
        for (int k=0; k<4; k++){
            strcpy(cursor, "?");
            cursor++;
            strcpy(cursor, s);
            cursor += s_len;
        }

        int *key_part_2 = calloc(key_len*5, sizeof(int));
        for(int k=0; k<key_len*5; k++){
            key_part_2[k] = key[k%key_len];
        }
        size_t s_len_part_2 = strlen(s_part_2);
        size_t key_len_part_2 = key_len*5;
        size_t *memo_2 = calloc(s_len_part_2 * key_len_part_2, sizeof(size_t));
        total_combos_part_2 += num_valid_combos_starting_from(s_part_2, key_part_2, s_len_part_2, key_len_part_2, 0, 0, memo_2);

        arrfree(key);
        free(s);
        free(memo);
        free(key_part_2);
        free(s_part_2);
        free(memo_2);
    }

    printf("Total combos: %zu\n", total_combos); 
    printf("Total combos part 2: %zu\n", total_combos_part_2); 
    free(lines);
}
#include <string.h>
#include <stdio.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    char *key;
    char **value;
} Node_To_Neighbours;

void part1(Node_To_Neighbours *adj, char *instructions, int instruction_length)
{
    char *current_node = "AAA";
    int step_count = 0;
    int i = 0;
    while (strcmp(current_node, "ZZZ") != 0)
    {
        char **current_node_neighbours = shget(adj, current_node);
        if (instructions[i] == 'L') current_node = current_node_neighbours[0];
        else current_node = current_node_neighbours[1];
        step_count++;
        i++;
        if (i == instruction_length) i = 0;
    }
    printf("Part1: %d\n", step_count);
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

    char *instructions = lines[0];
    int instruction_length = strlen(instructions);

    Node_To_Neighbours *adj = NULL;
    for (int i = 2; i < linecount; i++)
    {
        char *line = lines[i];
        line[3] = '\0';
        line[10] = '\0';
        line[15] = '\0';

        char **neighbours = malloc(2 * sizeof(char*));
        neighbours[0] = line + 7;
        neighbours[1] = line + 12;
        shput(adj, line, neighbours);
    }
    part1(adj, instructions, instruction_length);


    for (int i = 0; i < linecount; i++) free(lines[i]);
    free(lines);
    for (int i = 0; i < shlen(adj); i++) free(adj[i].value);
    hmfree(adj);


// Part2 pseudocode
// queue "level" with N items in it, ["BBA", "AAA", "CCA"], N is number of nodes that end in A

// int step_count = 0
// while (1)
    // int queue_all_z = 1
    // char *next_level[N] = {}
    // for (int i = 0; i < N; i++)
        // char *current_node = level[i]
        // char **current_node_neighbours = shget(adj, current_node)
        // if instructions[j] == 'L' next_node = current_node_neighbours[0]
        // else next_node = current_node_neighbours[1]
        // if next_node[2] != 'Z' queue_all_z = 0
        // next_level[i] = next_node
    // step_count++
    // if queue_all_z == 1 return step_count






    return 0;
}


// Process inputs
    // First line -> char array "instructions"
    // All other lines -> graph adjacency list, i.e.  hashmap {node: [neighbourL, neighbourR]}

// Traverse graph using adjacency list and insturctions, until reach node ZZZ. Assume able to reach ZZZ.

#include <string.h>
#include <stdio.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    int r;
    int c;
} Point;

Point find_starting_position(char **grid, int ROWS, int COLS)
{
    Point starting_position = {-1, -1};
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (grid[r][c] == 'S')
            {
                starting_position.r = r;
                starting_position.c = c;
                return starting_position;
            }
        }
    }
    return starting_position;
}

int dfs(char **grid, int ROWS, int COLS, Point pos, int *visited, Point end_pos, Point prev_pos)
{
    if (pos.r < 0 || pos.r >= ROWS || pos.c < 0 || pos.c >= COLS || grid[pos.r][pos.c] == '.'|| visited[pos.r * COLS + pos.c])
    {
        return -1;
    }
    if (pos.r == end_pos.r && pos.c == end_pos.c)
    {
        return 1;
    }

    visited[pos.r * COLS + pos.c] = 1;

    int res;
    if (grid[pos.r][pos.c] == '|' && prev_pos.r < pos.r){
        res = dfs(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == '|' && prev_pos.r > pos.r){
        res = dfs(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == '-' && prev_pos.c < pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == '-' && prev_pos.c > pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == 'L' && prev_pos.c == pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == 'L' && prev_pos.c != pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == 'J' && prev_pos.c == pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == 'J' && prev_pos.c != pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == '7' && prev_pos.c == pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == '7' && prev_pos.c != pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == 'F' && prev_pos.c == pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, end_pos, pos);
    }
    else if (grid[pos.r][pos.c] == 'F' && prev_pos.c != pos.c){
        res = dfs(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, end_pos, pos);
    }


    if (res != -1){
        return res + 1;
    }
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **grid = NULL;
    int ROWS = read_file_to_lines(&grid, file_path);
    int COLS = strlen(grid[0]);

    Point starting_position = find_starting_position(grid, ROWS, COLS);

    Point first_positions[4] = {
        {starting_position.r + 1, starting_position.c},
        {starting_position.r - 1, starting_position.c},
        {starting_position.r, starting_position.c + 1},
        {starting_position.r, starting_position.c - 1}
    };
    
    int *visited = malloc(ROWS * COLS * sizeof(int));
    int res;
    for (int i = 0; i < 4; i++)
    {
        res = dfs(grid, ROWS, COLS, first_positions[i], visited, starting_position, starting_position);
        if (res != -1) break;
    }
    
    printf("Part1: %d\n", (res) / 2);
}
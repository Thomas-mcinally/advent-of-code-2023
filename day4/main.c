#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int read_file_to_lines(char ***lines){
    int MAX_LINE_LENGTH = 256;
    FILE *file = fopen("./input.txt", "r");
    int lineCount = 0;

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        *lines = realloc(*lines, (lineCount + 1) * sizeof(char *));
        (*lines)[lineCount] = malloc(strlen(buffer) + 1);

        strcpy((*lines)[lineCount], buffer);
        lineCount++;
    }
    fclose(file);
    return lineCount;
}


int main()
{
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines);
    int *i_to_copies = malloc(lineCount * sizeof(int));
    for (int i = 0; i < lineCount; i++) i_to_copies[i] = 1;
    int total_score = 0;
    int total_scratchcards = 0;
    for (int i = 0; i < lineCount; i++)
    {
        int seen_nums[101] = {0}; 

        int cur_num = 0;
        for (int j = 10; lines[i][j] != '|'; j++)
        {
            if (isdigit(lines[i][j]))
            {
                cur_num *= 10;
                cur_num += lines[i][j] - '0';
            }
            else if (lines[i][j] == ' ' && cur_num != 0)
            {
                seen_nums[cur_num] = 1;
                cur_num = 0;
            }
        }


        cur_num = 0;
        int matches_found = 0;
        for (int j = 42; lines[i][j] != '\0'; j++)
        {
            if (isdigit(lines[i][j]))
            {
                cur_num *= 10;
                cur_num += lines[i][j] - '0';
            }
            else if (lines[i][j] == ' ')
            {
                if (seen_nums[cur_num]) matches_found += 1;
                cur_num = 0;
            }
        }
        if (seen_nums[cur_num]) matches_found += 1;
        if (matches_found != 0) total_score += pow(2, matches_found - 1);


        total_scratchcards += i_to_copies[i];
        for (int r = i+1; r < i+1+matches_found && r < lineCount; r++) i_to_copies[r] += i_to_copies[i];

        free(lines[i]);
    }
    free(lines);
    free(i_to_copies);
    printf("Part1: %i \n", total_score);
    printf("Part2: %i \n", total_scratchcards);
}
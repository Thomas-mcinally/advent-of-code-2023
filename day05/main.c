#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include "aoc_lib.h"

#define SENTINEL_VALUE 0x7FFFFFFFFFFFFFFF // max long long int value

void get_list_of_intervals_from_raw_input(char **lines, long long int list_of_intervals[100][3], int line_count)
{
  for (int i = 0; i < line_count; i++)
  {
    int j = 0;
    long long int first_num = extract_number_from_string_starting_from(lines[i], &j);
    j++;
    long long int second_num = extract_number_from_string_starting_from(lines[i], &j);
    j++;
    long long int third_num = extract_number_from_string_starting_from(lines[i], &j);

    list_of_intervals[i][0] = second_num;
    list_of_intervals[i][1] = second_num + third_num - 1;
    list_of_intervals[i][2] = first_num - second_num;
  }

  list_of_intervals[line_count][0] = SENTINEL_VALUE; // denote end of array
}

void get_list_of_seeds_from_raw_input(char *seed_line, long long int seeds[100])
{
  printf("processing seed line: %s\n", seed_line);
  int i = 0;
  int j = 7;

  while (seed_line[j] != '\0')
  {
    long long int next_num = extract_number_from_string_starting_from(seed_line, &j);
    if (seed_line[j] == ' ') j++;
    seeds[i] = next_num;
    i++;
  };
  seeds[i] = SENTINEL_VALUE; // denote end of array
}

long long int get_destination_from_source_and_intervals(long long int list_of_intervals[100][3], long long int source_val)
{
  for (int i = 0; list_of_intervals[i][0] != SENTINEL_VALUE; i++)
  {
    if (source_val >= list_of_intervals[i][0] && source_val <= list_of_intervals[i][1])
    {
      return source_val + list_of_intervals[i][2];
    }
  }
  return source_val;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
    exit(1);
  }

  char *file_path = argv[1];
  char *file_contents = read_entire_file(file_path);
  char **sections = NULL;
  const int section_count = split_string_by_delimiter_string(file_contents, "\n\n", &sections);
  const int number_of_maps = section_count - 1;
  long long int maps[number_of_maps][100][3]; //assume each section has max 100 lines
  for (int i = 0; i < number_of_maps; i++)
  {
    char **section_lines = NULL;
    const int line_count = split_string_by_delimiter_string(sections[i+1],"\n", &section_lines);
    section_lines++; //first line is name of the map
    get_list_of_intervals_from_raw_input(section_lines, maps[i], line_count-1);
    section_lines--;
    for (int j = 0; j < line_count; j++) free(section_lines[j]);
    free(section_lines);
  }
  free(file_contents);
  
  long long int seeds[100]; //assume max 100 seeds
  get_list_of_seeds_from_raw_input(sections[0], seeds);

  for (int i = 0; i < section_count; i++) free(sections[i]);
  free(sections);

  long long int lowest_location = SENTINEL_VALUE;
  for (int i = 0; seeds[i] != SENTINEL_VALUE; i++)
  {
    long long int step = seeds[i];

    for (int j = 0; j < number_of_maps; j++)
    {
      step = get_destination_from_source_and_intervals(maps[j], step);
    }

    if (step < lowest_location)
    {
      lowest_location = step;
    }
  }
  printf("Part1 sol: %lli\n", lowest_location);
}

// Think of as interval question, use input to form a list of non-overlapping intervals

// ASSUMPTIONS
// - Can assume input given in predictable ladder format, where each map gives output that is input for the next map
// - Currently assume each map has a maximum of 100 lines.
// - Currently assume there are max 100 initial seeds
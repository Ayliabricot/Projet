#ifndef MAP
#define MAP

char** create_map(int rows, int cols);
void display_map();
void free_map(char** map, int rows);

#endif
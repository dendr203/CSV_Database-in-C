#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void parametry_check(char **cesta_in, char **cesta_out, int argc, char **argv);

void stats(char **buffer, int *rows, int *cols);

void create(char **text, char **buffer, int rows);

void addrow(char **text, char **command, int rows);

void addcol(char **text, char **command, int rows);

bool test_stats(char **command, int *rows, int *cols);

bool existuje(char **text, char **command, int rows, int cols);

void average(char **text, char **command, int rows, int cols);

void max(char **text, char **command, int rows, int cols);

void min(char **text, char **command, int rows, int cols);

void sum(char **text, char **command, int rows, int cols);

void destroy_arr(char **text, int rows);

void destroy_in_out(char **cesta_in, char **cesta_out);
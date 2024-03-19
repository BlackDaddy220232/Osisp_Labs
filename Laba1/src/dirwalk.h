#ifndef DIRWALK_H
#define DIRWALK_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include<getopt.h>

int compare(const struct dirent **a, const struct dirent **b);
void print_entry(const char *path, int options);
void dirwalk(const char *dir, int options);
void process_options(int argc, char *argv[], char **dir, int *options);
int compare_wrapper(const void *a, const void *b);
#endif /* DIRWALK_H */
